/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:35:09 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 11:43:45 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
open_heredoc

Propósito:
    Maneja la entrada de datos para una redirección `<<` heredoc.

Lógica:
    1. Cierra el extremo de lectura del pipe heredoc si está abierto.
    2. Lee líneas de entrada del usuario con `readline`.
    3. Finaliza si la entrada coincide con el delimitador (`limiter`).
    4. Expande variables en la línea con `expand_later`.
    5. Escribe la línea, seguida de un salto de línea, en el pipe heredoc.
    6. Finaliza el proceso heredoc con `exit(0)`.

Comentarios:
    Implementa la lógica para capturar múltiples líneas en un heredoc.
*/

static void	open_heredoc(t_data *data)
{
	char	*limiter;
	char	*line;
	char	*endl;

	if (data->l_pipe[0] != -1)
		close(data->l_pipe[0]);
	limiter = data->heredoc;
	while (1)
	{
		line = readline("> ");
		if (!line)
			exit(1);
		if (!ft_strcmp(line, limiter))
		{
			free(line);
			break ;
		}
		expand_later(data, &line);
		endl = ft_strjoin(line, "\n");
		write(data->l_pipe[1], endl, ft_strlen(endl));
		free(line);
		free(endl);
	}
	exit(0);
}

/*
write_heredoc

Propósito:
    Ejecuta el proceso heredoc para capturar y escribir datos.

Lógica:
    1. Crea un nuevo proceso hijo con `fork`.
    2. En el hijo:
        - Configura la señal `SIGINT` para su manejo predeterminado.
        - Llama a `open_heredoc` para procesar las entradas heredoc.
    3. En el padre:
        - Espera al proceso hijo con `waitpid`.
        - Verifica el estado de salida para manejar errores o interrupciones.
    4. Retorna 130 si el heredoc es interrumpido, 0 si finaliza correctamente.

Comentarios:
    Coordina la ejecución del heredoc y gestiona interrupciones.
*/

int	write_heredoc(t_data *data)
{
	int		pid;

	pid = fork();
	if (pid == -1)
		return (1);
	g_signal = pid;
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		open_heredoc(data);
	}
	waitpid(pid, &(data->status), 0);
	if (!WIFEXITED(data->status))
		return (130);
	else if (WEXITSTATUS(data->status) == 1)
		exit_builtin(data, NULL);
	return (0);
}

/*
Resumen del archivo

Propósito:
    Implementa la lógica para manejar la redirección heredoc (`<<`).

Lógica:
    1. open_heredoc: Procesa la entrada heredoc, expandiendo variables y
	escribiendo en el pipe.
    2. write_heredoc: Coordina la ejecución del proceso heredoc y
	gestiona su estado.

Comentarios:
    Este archivo implementa una parte fundamental para manejar entradas
    dinámicas en scripts y comandos interactivos.
*/
