/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j_history.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:17:10 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 10:49:01 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
get_history

Propósito:
    Carga el historial del shell desde un archivo temporal.

Lógica:
    1. Define la ruta al archivo de historial (`/tmp/.ms_history`).
    2. Si el archivo existe, lo lee usando `read_history`.

Comentarios:
    Permite persistir el historial del shell entre sesiones.
*/

void	get_history(void)
{
	char	*ms_history;

	ms_history = "/tmp/.ms_history";
	if (ms_history)
		read_history(ms_history);
}

/*
save_history

Propósito:
    Guarda el historial del shell en un archivo temporal.

Lógica:
    1. Define la ruta al archivo de historial (`/tmp/.ms_history`).
    2. Si la ruta es válida, escribe el historial con `write_history`.

Comentarios:
    Asegura que el historial del shell se guarde al finalizar la sesión.
*/

void	save_history(void)
{
	char	*ms_history;

	ms_history = "/tmp/.ms_history";
	if (ms_history)
		write_history(ms_history);
}

/*
Resumen del archivo

Propósito:
    Gestiona la lectura y escritura del historial del shell en un archivo.

Lógica:
    1. get_history: Carga el historial desde un archivo temporal.
    2. save_history: Guarda el historial en un archivo temporal.

Comentarios:
    Este archivo implementa la persistencia del historial entre sesiones
    de shell utilizando funciones de manejo de historial.
*/
