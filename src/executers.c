/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:06:51 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 11:30:58 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
builtin_out

Propósito:
    Ejecuta un comando interno (builtin) del shell.

Lógica:
    1. Compara el comando con una lista de builtins (`exit`, `echo`, `cd`, etc.).
    2. Llama a la función correspondiente para ejecutar el builtin.
    3. Si el comando está en un proceso hijo (`fork == 1`),
	llama a `exit` con el estado.
    4. Retorna el código de estado del builtin ejecutado.

Comentarios:
    Gestiona la ejecución de comandos internos con o sin forks.
*/

int	builtin_out(t_data *data, t_cmd *cmd, int fork)
{
	int	status;

	status = 0;
	if (!ft_strcmp(cmd->cmd, "exit"))
		status = exit_builtin(data, cmd);
	else if (!ft_strcmp(cmd->cmd, "echo"))
		status = echo_builtin(cmd);
	else if (!ft_strcmp(cmd->cmd, "cd"))
		status = cd_builtin(data, cmd);
	else if (!ft_strcmp(cmd->cmd, "pwd"))
		status = pwd_builtin(data);
	else if (!ft_strcmp(cmd->cmd, "export"))
		status = export_builtin(data, cmd);
	else if (!ft_strcmp(cmd->cmd, "unset"))
		status = unset_builtin(data, cmd);
	else if (!ft_strcmp(cmd->cmd, "env"))
		status = env_builtin(data);
	else if (!ft_strcmp(cmd->cmd, "history"))
		status = history_builtin();
	if (fork)
		exit (status);
	return (status);
}
/*
builtin_redir

Propósito:
    Ejecuta un comando interno con redirecciones de salida configuradas.

Lógica:
    1. Cierra el descriptor de entrada si está abierto (`fd[0]`).
    2. Duplica el descriptor de salida (`fd[1]`) a `STDOUT_FILENO`
	si está configurado.
    3. Ejecuta el builtin usando `builtin_out`.
    4. Restaura la salida estándar si fue redirigida.
    5. Retorna el código de estado del builtin ejecutado.

Comentarios:
    Gestiona builtins que requieren redirecciones de salida.
*/

int	builtin_redir(t_data *data, t_cmd *cmd)
{
	int	exit_code;
	int	stdout_fd;

	stdout_fd = -1;
	if (data->fd[0] != -1)
	{
		close(data->fd[0]);
		data->fd[0] = -1;
	}
	if (data->fd[1] != -1)
	{
		stdout_fd = dup(STDOUT_FILENO);
		dup2(data->fd[1], STDOUT_FILENO);
		close(data->fd[1]);
		data->fd[1] = -1;
	}
	exit_code = builtin_out(data, cmd, 0);
	if (stdout_fd != -1)
	{
		dup2(stdout_fd, STDOUT_FILENO);
		close(stdout_fd);
	}
	return (exit_code);
}

/*
cmd_out

Propósito:
    Ejecuta un comando externo usando `execve`.

Lógica:
    1. Obtiene la ruta y los argumentos del comando.
    2. Si la ruta es nula, termina el proceso con `exit(1)`.
    3. Llama a `execve` para ejecutar el comando con el entorno actual.
    4. Si `execve` falla, llama a `execve_error` y termina con `exit`.

Comentarios:
    Maneja la ejecución de comandos externos en el shell.
*/

void	cmd_out(t_data *data, t_cmd *command)
{
	char	*path;
	char	**args;

	path = command->cmd;
	args = command->args;
	if (!path)
		exit(1);
	if (execve(path, args, data->envp) == -1)
		exit(execve_error(data, command));
}

/*
Resumen del archivo

Propósito:
    Proporciona funciones para ejecutar comandos internos y externos.

Lógica:
    1. builtin_out: Ejecuta comandos internos con opciones de fork.
    2. builtin_redir: Maneja redirecciones de salida para comandos internos.
    3. cmd_out: Ejecuta comandos externos usando `execve`.

Comentarios:
    Este archivo implementa la lógica principal para la ejecución de comandos
    en el shell, tanto internos como externos.
*/
