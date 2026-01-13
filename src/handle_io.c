/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:32:54 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 11:30:18 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
replace_in_fd

Propósito:
    Redirige el descriptor de entrada estándar (`STDIN_FILENO`) a `fd[0]`.

Lógica:
    1. Duplica `fd[0]` a `STDIN_FILENO` usando `dup2`.
    2. Cierra `fd[0]` tras duplicarlo.
    3. Retorna 1 si ocurre un error al duplicar.

Comentarios:
    Maneja redirecciones de entrada desde un archivo.
*/

static int	replace_in_fd(t_data *data)
{
	if (dup2(data->fd[0], STDIN_FILENO) == -1)
	{
		close(data->fd[0]);
		return (1);
	}
	close(data->fd[0]);
	return (0);
}

/*
replace_in_pipe

Propósito:
    Redirige la entrada estándar (`STDIN_FILENO`) al extremo de lectura del pipe.

Lógica:
    1. Cierra el extremo de escritura del pipe izquierdo (`l_pipe[1]`).
    2. Duplica `l_pipe[0]` a `STDIN_FILENO` usando `dup2`.
    3. Cierra `l_pipe[0]` tras duplicarlo.
    4. Retorna 1 si ocurre un error al duplicar.

Comentarios:
    Configura la entrada estándar para leer desde un pipe.
*/

static int	replace_in_pipe(t_data *data)
{
	close(data->l_pipe[1]);
	if (dup2(data->l_pipe[0], STDIN_FILENO) == -1)
	{
		close(data->l_pipe[0]);
		return (1);
	}
	close(data->l_pipe[0]);
	return (0);
}

/*
replace_out_fd

Propósito:
    Redirige la salida estándar (`STDOUT_FILENO`) a `fd[1]`.

Lógica:
    1. Duplica `fd[1]` a `STDOUT_FILENO` usando `dup2`.
    2. Cierra `fd[1]` tras duplicarlo.
    3. Retorna 1 si ocurre un error al duplicar.

Comentarios:
    Maneja redirecciones de salida hacia un archivo.
*/

static int	replace_out_fd(t_data *data)
{
	if (dup2(data->fd[1], STDOUT_FILENO) == -1)
	{
		close(data->fd[1]);
		return (1);
	}
	close(data->fd[1]);
	return (0);
}

/*
replace_out_pipe

Propósito:
    Redirige la salida estándar (`STDOUT_FILENO`)
	al extremo de escritura del pipe.

Lógica:
    1. Cierra el extremo de lectura del pipe derecho (`r_pipe[0]`).
    2. Duplica `r_pipe[1]` a `STDOUT_FILENO` usando `dup2`.
    3. Cierra `r_pipe[1]` tras duplicarlo.
    4. Retorna 1 si ocurre un error al duplicar.

Comentarios:
    Configura la salida estándar para escribir en un pipe.
*/

static int	replace_out_pipe(t_data *data)
{
	close(data->r_pipe[0]);
	if (dup2(data->r_pipe[1], STDOUT_FILENO) == -1)
	{
		close(data->r_pipe[1]);
		return (1);
	}
	close(data->r_pipe[1]);
	return (0);
}

/*
handle_io

Propósito:
    Configura las redirecciones de entrada y salida
	según los descriptores abiertos.

Lógica:
    1. Si `fd[0]` está abierto, redirige entrada estándar con `replace_in_fd`.
    2. Si no, redirige entrada estándar desde `l_pipe[0]` con `replace_in_pipe`.
    3. Si `fd[1]` está abierto, redirige salida estándar con `replace_out_fd`.
    4. Si no, redirige salida estándar a `r_pipe[1]` con `replace_out_pipe`.

Comentarios:
    Maneja todas las redirecciones de entrada/salida
	para la ejecución de comandos.
*/

int	handle_io(t_data *data)
{
	if (data->fd[0] != -1)
	{
		if (replace_in_fd(data) == 1)
			return (1);
	}
	else if (data->l_pipe[0] != -1)
	{
		if (replace_in_pipe(data) == 1)
			return (1);
	}
	if (data->fd[1] != -1)
	{
		if (replace_out_fd(data) == 1)
			return (1);
	}
	else if (data->r_pipe[1] != -1)
	{
		if (replace_out_pipe(data) == 1)
			return (1);
	}
	return (0);
}

/*
Resumen del archivo

Propósito:
    Implementa la lógica de redirección de entrada y salida estándar.

Lógica:
    1. replace_in_fd: Redirige entrada estándar desde un archivo.
    2. replace_in_pipe: Redirige entrada estándar desde un pipe.
    3. replace_out_fd: Redirige salida estándar a un archivo.
    4. replace_out_pipe: Redirige salida estándar a un pipe.
    5. handle_io: Coordina las redirecciones de entrada y salida
	según el contexto.

Comentarios:
    Este archivo garantiza la correcta configuración de I/O
	antes de ejecutar comandos.
*/
