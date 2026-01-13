/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:37:35 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 11:45:05 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
print_local_error

Propósito:
    Imprime un mensaje de error para una variable local no encontrada.

Lógica:
    1. Muestra el token seguido del mensaje "not found" en la salida de error.
    2. Utiliza `ft_putstr_fd` y `ft_putendl_fd` para escribir en `stderr`.

Comentarios:
    Maneja errores relacionados con identificadores no válidos
	de variables locales.
*/

static void	print_local_error(char	*token)
{
	ft_putstr_fd(token, 2);
	ft_putendl_fd(": " NOT_FOUND, 2);
}

/*
id_error

Propósito:
    Verifica si un identificador es válido y maneja errores de export o local.

Lógica:
    1. Comprueba la validez del identificador con `valid_ident`.
    2. Si no es válido:
        - Llama a `print_local_error` o construye un mensaje personalizado.
        - Retorna 1 para indicar error.
    3. Retorna 0 si no hay error.

Comentarios:
    Valida identificadores para exportaciones y variables locales.
*/

int	id_error(t_data *data, char *arg, char *variable, int exp)
{
	if (variable && !valid_ident(variable))
	{
		if (!exp)
			print_local_error(arg);
		else
		{
			ft_putstr_fd(MS "`", 2);
			ft_putstr_fd(arg, 2);
			print_msg(data, "': " EXPORT_ID, 2);
		}
		return (1);
	}
	else if (!variable && !valid_ident(arg))
	{
		if (!exp)
			print_local_error(arg);
		else
		{
			ft_putstr_fd(MS "`", 2);
			ft_putstr_fd(arg, 2);
			print_msg(data, "': " EXPORT_ID, 2);
		}
		return (1);
	}
	return (0);
}

/*
handle_errno

Propósito:
    Muestra un mensaje de error relacionado con el valor actual de `errno`.

Lógica:
    1. Si `errno` está establecido:
        - Imprime el mensaje del shell, el wildcard y el error de sistema.
        - Retorna 1 para indicar que ocurrió un error.
    2. Si no hay error, retorna 0.

Comentarios:
    Facilita la impresión de mensajes de error del sistema para diagnósticos.
*/

int	handle_errno(char *wildcard)
{
	if (errno)
	{
		ft_putstr_fd(MS, 2);
		ft_putstr_fd(wildcard, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	return (0);
}

/*
execve_error

Propósito:
    Muestra un mensaje de error relacionado con la ejecución de un comando.

Lógica:
    1. Imprime el nombre del comando y el mensaje de error asociado.
    2. Si el comando no contiene una barra (`/`), indica que no fue encontrado.
    3. Si el comando apunta a un directorio, indica "Is a directory".
    4. Retorna códigos de error estándar (126, 127) según el tipo de error.

Comentarios:
    Maneja errores de ejecución de comandos, como permisos o inexistencia.
*/

int	execve_error(t_data *data, t_cmd *cmd)
{
	int	code;

	code = errno;
	ft_putstr_fd(MS, 2);
	ft_putstr_fd(data->last_cmd->token, 2);
	ft_putstr_fd(": ", 2);
	if (!ft_strchr(cmd->cmd, '/'))
	{
		ft_putendl_fd(NOT_FOUND, 2);
		return (127);
	}
	else
	{
		if (!stat(data->last_cmd->token, &(data->stat)) && \
		S_ISDIR(data->stat.st_mode) && \
		ft_strchr(cmd->cmd, '/'))
			ft_putendl_fd(IS_DIR, 2);
		else
		{
			ft_putendl_fd(strerror(code), 2);
			if (code == 2)
				return (127);
		}
		return (126);
	}
}

/*
Resumen del archivo

Propósito:
    Proporciona funciones para manejar y reportar errores en el shell.

Lógica:
    1. print_local_error: Imprime errores para variables locales no válidas.
    2. id_error: Verifica y maneja errores en identificadores.
    3. handle_errno: Muestra errores del sistema usando `errno`.
    4. execve_error: Maneja errores al ejecutar comandos externos.

Comentarios:
    Este archivo centraliza la lógica de manejo de errores, garantizando
    mensajes claros y códigos de retorno estándar.
*/
