/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:41:47 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 11:25:32 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
open_infile

Propósito:
    Abre un archivo de entrada en modo lectura.

Lógica:
    1. Cierra cualquier archivo de entrada previo con `close_infiles`.
    2. Verifica si el archivo es un directorio usando `stat`.
    3. Si no es un directorio, abre el archivo en modo `O_RDONLY`.
    4. Maneja errores y actualiza `data->fd[0]` con el descriptor.

Comentarios:
    Maneja la apertura de archivos para redirecciones de entrada (`<`).
*/

static int	open_infile(t_data *data, t_token *token)
{
	char	*file;

	file = token->token;
	close_infiles(data);
	if (!stat(file, &(data->stat)) && S_ISDIR(data->stat.st_mode))
	{
		ft_putstr_fd(MS, 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(": " IS_DIR, 2);
		return (1);
	}
	data->fd[0] = open(file, O_RDONLY);
	if (data->fd[0] == -1)
		return (handle_errno(file), 1);
	data->heredoc = NULL;
	return (0);
}

/*
open_heredoc

Propósito:
    Configura una redirección heredoc y escribe los datos en un pipe.

Lógica:
    1. Cierra cualquier archivo de entrada previo con `close_infiles`.
    2. Crea un pipe para el heredoc con `pipe(data->l_pipe)`.
    3. Mueve al siguiente token y procesa el heredoc con `write_heredoc`.
    4. Retorna 130 si el heredoc se interrumpe.

Comentarios:
    Implementa la lógica necesaria para manejar redirecciones `<<`.
*/

static int	open_heredoc(t_data *data)
{
	close_infiles(data);
	if (pipe(data->l_pipe) == -1)
		return (1);
	data->input.tokens = data->input.tokens->next;
	data->heredoc = data->input.tokens->token;
	if (write_heredoc(data) == 130)
		return (130);
	return (0);
}

/*
trunc_file

Propósito:
    Abre o crea un archivo en modo sobrescritura para redirección de salida.

Lógica:
    1. Cierra cualquier archivo de salida previo (`data->fd[1]`).
    2. Abre el archivo en modo `O_CREAT | O_TRUNC | O_WRONLY`.
    3. Si hay errores, los maneja con `handle_errno`.

Comentarios:
    Maneja redirecciones de salida estándar (`>`).
*/

static int	trunc_file(t_data *data, t_token *token)
{
	char	*file;

	if (data->fd[1] != -1)
		close(data->fd[1]);
	file = token->token;
	data->fd[1] = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (data->fd[1] == -1)
		return (handle_errno(file), 1);
	data->input.tokens = data->input.tokens->next;
	return (0);
}

/*
append_file

Propósito:
    Abre o crea un archivo en modo adición para redirección de salida.

Lógica:
    1. Cierra cualquier archivo de salida previo (`data->fd[1]`).
    2. Abre el archivo en modo `O_CREAT | O_APPEND | O_WRONLY`.
    3. Maneja errores y avanza al siguiente token.

Comentarios:
    Implementa redirecciones de salida en modo adición (`>>`).
*/

static int	append_file(t_data *data, t_token *token)
{
	char	*file;

	if (data->fd[1] != -1)
		close(data->fd[1]);
	file = token->token;
	data->fd[1] = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (data->fd[1] == -1)
		return (handle_errno(file), 1);
	data->input.tokens = data->input.tokens->next;
	return (0);
}

/*
open_files

Propósito:
    Gestiona la apertura de archivos según las redirecciones encontradas.

Lógica:
    1. Itera sobre los tokens hasta encontrar un pipe o el final.
    2. Llama a funciones específicas según el tipo de redirección
       (`LEFT`, `LEFTT`, `RIGHT`, `RIGHTT`).
    3. Retorna el estado en caso de error y salta a los siguientes comandos.

Comentarios:
    Es la función central para procesar todas las redirecciones de archivos.
*/

int	open_files(t_data *data)
{
	int	status;

	status = 0;
	while (data->input.tokens && data->input.tokens->type != PIPE)
	{
		if (data->input.tokens->type == LEFT)
			status = open_infile(data, data->input.tokens->next);
		else if (data->input.tokens->type == LEFTT)
			status = open_heredoc(data);
		else if (data->input.tokens->type == RIGHT)
			status = trunc_file(data, data->input.tokens->next);
		else if (data->input.tokens->type == RIGHTT)
			status = append_file(data, data->input.tokens->next);
		data->input.tokens = data->input.tokens->next;
		if (status)
		{
			while (data->input.tokens && data->input.tokens->type != CMD)
				data->input.tokens = data->input.tokens->next;
			return (status);
		}
	}
	if (data->input.tokens)
		data->input.tokens = data->input.tokens->next;
	return (0);
}

/*
Resumen del archivo

Propósito:
    Gestiona la apertura de archivos y pipes según las redirecciones
	de la entrada.

Lógica:
    1. open_infile: Abre archivos de entrada (`<`).
    2. open_heredoc: Maneja redirecciones heredoc (`<<`).
    3. trunc_file: Abre archivos en modo sobrescritura (`>`).
    4. append_file: Abre archivos en modo adición (`>>`).
    5. open_files: Coordina la apertura de archivos y gestiona errores.

Comentarios:
    Este archivo implementa la lógica para configurar la I/O basada en las
    redirecciones especificadas por el usuario.
*/
