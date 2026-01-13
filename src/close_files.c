/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 12:04:05 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 11:28:11 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
close_infiles

Propósito:
    Cierra los descriptores de entrada y los pipes abiertos.

Lógica:
    1. Cierra el descriptor de entrada en `fd[0]` si está abierto.
    2. Cierra ambos extremos de los pipes (`r_pipe` y `l_pipe`)
	si están abiertos.
    3. Establece todos los descriptores cerrados a `-1`.

Comentarios:
    Garantiza la liberación de recursos relacionados con la entrada y pipes.
*/

void	close_infiles(t_data *data)
{
	if (data->fd[0] != -1)
		close(data->fd[0]);
	if (data->r_pipe[0] != -1)
		close(data->r_pipe[0]);
	if (data->r_pipe[1] != -1)
		close(data->r_pipe[1]);
	data->r_pipe[0] = -1;
	data->r_pipe[1] = -1;
	if (data->l_pipe[0] != -1)
		close(data->l_pipe[0]);
	if (data->l_pipe[1] != -1)
		close(data->l_pipe[1]);
	data->l_pipe[0] = -1;
	data->l_pipe[1] = -1;
}

/*
close_parent_files

Propósito:
    Cierra los descriptores y pipes abiertos en el proceso padre.

Lógica:
    1. Cierra ambos extremos del pipe izquierdo (`l_pipe`) si están abiertos.
    2. Cierra los descriptores de entrada y salida (`fd[0]` y `fd[1]`)
	si están abiertos.
    3. Establece todos los descriptores cerrados a `-1`.

Comentarios:
    Limpia los descriptores y pipes usados por el proceso padre
	tras la ejecución.
*/

void	close_parent_files(t_data *data)
{
	if (data->l_pipe[0] != -1)
		close(data->l_pipe[0]);
	if (data->l_pipe[1] != -1)
		close(data->l_pipe[1]);
	data->l_pipe[0] = -1;
	data->l_pipe[1] = -1;
	if (data->fd[0] != -1)
		close(data->fd[0]);
	if (data->fd[1] != -1)
		close(data->fd[1]);
	data->fd[0] = -1;
	data->fd[1] = -1;
}

/*
Resumen del archivo

Propósito:
    Gestiona el cierre de descriptores de archivos y pipes para liberar recursos.

Lógica:
    1. close_infiles: Cierra descriptores de entrada y pipes abiertos.
    2. close_parent_files: Cierra descriptores y pipes del proceso padre.

Comentarios:
    Este archivo asegura la limpieza y liberación de recursos asociados con
    la entrada y pipes tras la ejecución de comandos.
*/
