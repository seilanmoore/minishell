/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_io.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:58:17 by smoore-a          #+#    #+#             */
/*   Updated: 2025/01/20 22:27:16 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
wait_children

Propósito:
    Espera a que todos los procesos hijo terminen y captura su estado.

Lógica:
    1. Usa `waitpid` para esperar a cada proceso hijo.
    2. Si no termina normalmente y no hay señal, retorna 130.
    3. Si termina por señal (SIGQUIT), imprime mensaje y retorna 131.
    4. Si termina normalmente, retorna el código de salida.

Comentarios:
    Maneja el estado de los procesos hijo y las señales asociadas.
*/

static int	wait_children(t_data *data, pid_t *pid)
{
	int	i;

	i = -1;
	while (++i < data->n_cmd)
		waitpid(pid[i], &data->status, 0);
	if (!WIFEXITED(data->status) && !g_signal)
		return (130);
	else if (!WIFEXITED(data->status) && g_signal)
	{
		ft_putendl_fd("Quit (core dumped)", 2);
		return (131);
	}
	else if (WIFEXITED(data->status))
		return (WEXITSTATUS(data->status));
	else
		return (0);
}

/*
child_exe

Propósito:
    Ejecuta un comando en un proceso hijo.

Lógica:
    1. Si es el proceso hijo (`pid == 0`), ajusta las señales y maneja la I/O.
    2. Ejecuta el comando como interno (`builtin_out`) o externo (`cmd_out`).
    3. Termina el proceso hijo con `exit` y el código de error.

Comentarios:
    Separa la lógica del hijo del padre, manejando la ejecución en paralelo.
*/

static int	child_exe(t_data *data, pid_t *pid, t_token *cmd)
{
	int	fail;

	fail = 0;
	g_signal = *pid;
	if (*pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		fail = handle_io(data);
		if (cmd->cmd->builtin && !fail)
			builtin_out(data, cmd->cmd, 1);
		else if (!fail)
			cmd_out(data, cmd->cmd);
		exit (fail);
	}
	close_parent_files(data);
	return (0);
}

/*
cmd_exe

Propósito:
    Gestiona la ejecución de un comando, ya sea interno o externo.

Lógica:
    1. Si no hay pipes y es un comando interno, redirige con `builtin_redir`.
    2. Si hay pipes, cambia y abre pipes con `change_pipe` y `open_r_pipe`.
    3. Crea un proceso hijo con `fork` y llama a `child_exe`.

Comentarios:
    Coordina la ejecución de comandos con o sin pipes.
*/

static int	cmd_exe(t_data *data, pid_t *pid, t_token *cmd)
{
	if (cmd->cmd->builtin && data->n_pipe == 0)
		return (builtin_redir(data, cmd->cmd));
	else
	{
		if (change_pipe(data))
			return (1);
		if (open_r_pipe(data))
			return (1);
		*pid = fork();
		if (*pid == -1)
			return (1);
		return (child_exe(data, pid, cmd));
	}
}

/*
cmd_io

Propósito:
    Maneja la entrada/salida y la ejecución del comando actual.

Lógica:
    1. Abre archivos relacionados con redirecciones usando `open_files`.
    2. Si hay errores en archivos o pipes, retorna el código de error.
    3. Llama a `cmd_exe` para ejecutar el comando.

Comentarios:
    Integra la lógica de redirección, pipes y ejecución para un comando.
*/

static int	cmd_io(t_data *data, pid_t *pid)
{
	t_token	*cmd;
	int		exit_var;

	exit_var = 0;
	cmd = data->input.tokens;
	data->last_cmd = cmd;
	data->input.tokens = data->input.tokens->next;
	exit_var = open_files(data);
	if (exit_var)
	{
		if (open_r_pipe(data) == 1)
			return (1);
		return (exit_var);
	}
	return (cmd_exe(data, pid, cmd));
}

/*
execute

Propósito:
    Ejecuta todos los comandos en la línea de entrada.

Lógica:
    1. Inicializa un array de `pid` para manejar procesos.
    2. Itera sobre los tokens para procesar redirecciones y comandos.
    3. Llama a `cmd_io` para cada comando y espera con `wait_children`.
    4. Libera recursos y retorna el código de salida.

Comentarios:
    Es el punto de entrada principal para la ejecución de la línea de entrada.
*/

int	execute(t_data *data)
{
	int		i;
	int		exit_var;

	if (!data->n_cmd)
		return (data->exit_code);
	data->first_token = data->input.tokens;
	data->pids = ft_calloc(data->n_cmd, sizeof(pid_t));
	if (!data->pids)
		return (0);
	exit_var = -1;
	i = -1;
	while (data->input.tokens && exit_var != 130)
	{
		if (is_redir(data->input.tokens->type))
			exit_var = open_files(data);
		else if (data->input.tokens->type == CMD)
			exit_var = cmd_io(data, &(data->pids[++i]));
	}
	if ((!data->last_cmd->cmd->builtin || data->n_pipe) && exit_var != 1)
		exit_var = wait_children(data, data->pids);
	ft_free((void *)&(data->pids));
	data->input.tokens = data->first_token;
	return (exit_var);
}

/*
Resumen del archivo

Propósito:
    Implementa la ejecución de comandos, manejando procesos, redirecciones
    y pipes.

Lógica:
    1. wait_children: Espera a los procesos hijo y maneja su estado.
    2. child_exe: Ejecuta un comando en un proceso hijo.
    3. cmd_exe: Coordina la ejecución de comandos internos o externos.
    4. cmd_io: Maneja redirecciones, pipes y ejecución de comandos.
    5. execute: Ejecuta todos los comandos de entrada.

Comentarios:
    Este archivo gestiona toda la lógica relacionada con la ejecución de
    procesos y la interacción con I/O en el shell.
*/
