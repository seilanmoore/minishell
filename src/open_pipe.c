/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:28:40 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 11:26:43 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
change_pipe

Propósito:
    Cambia el pipe de lectura a escritura y gestiona la herencia de pipes.

Lógica:
    1. Si el pipe de lectura (`r_pipe`) está abierto:
        - Cierra los pipes de lectura y escritura previos (`l_pipe`).
        - Duplica los descriptores de `r_pipe` a `l_pipe` si no hay heredoc.
    2. Cierra los descriptores actuales de `r_pipe`.
    3. Resetea los valores de `r_pipe` y `heredoc`.

Comentarios:
    Gestiona el flujo de datos entre múltiples comandos conectados por pipes.
*/

int	change_pipe(t_data *data)
{
	if (data->r_pipe[0] != -1)
	{
		if (!(data->heredoc) && data->fd[0] == -1)
		{
			if (data->l_pipe[0] != -1)
				close(data->l_pipe[0]);
			if (data->l_pipe[1] != -1)
				close(data->l_pipe[1]);
			if (pipe(data->l_pipe) == -1)
				return (1);
			dup2(data->r_pipe[0], data->l_pipe[0]);
			dup2(data->r_pipe[1], data->l_pipe[1]);
		}
		if (data->r_pipe[0] != -1)
			close(data->r_pipe[0]);
		if (data->r_pipe[1] != -1)
			close(data->r_pipe[1]);
		data->r_pipe[0] = -1;
		data->r_pipe[1] = -1;
	}
	data->heredoc = NULL;
	return (0);
}

/*
open_r_pipe

Propósito:
    Abre un nuevo pipe de escritura para el siguiente comando.

Lógica:
    1. Verifica si el token actual es precedido por un pipe.
    2. Si es así, crea un nuevo pipe en `r_pipe`.
    3. Retorna 1 si ocurre un error al crear el pipe.

Comentarios:
    Configura pipes para comandos consecutivos en una tubería.
*/

int	open_r_pipe(t_data *data)
{
	if (data->input.tokens)
	{
		if (data->input.tokens->prev && \
		data->input.tokens->prev->type == PIPE && \
		pipe(data->r_pipe) == -1)
			return (1);
	}
	return (0);
}

/*
Resumen del archivo

Propósito:
    Gestiona la configuración y transición entre pipes en comandos encadenados.

Lógica:
    1. change_pipe: Transfiere datos de un pipe de lectura a escritura.
    2. open_r_pipe: Crea un nuevo pipe para el siguiente comando.

Comentarios:
    Este archivo asegura la correcta configuración de pipes en escenarios
    con múltiples comandos conectados.
*/
