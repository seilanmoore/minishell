/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:02:07 by smoore-a          #+#    #+#             */
/*   Updated: 2025/01/20 22:28:48 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
ft_free

Propósito:
    Libera memoria de una cadena y la inicializa a `NULL`.

Lógica:
    1. Verifica si la cadena no es nula.
    2. Libera la memoria asociada a la cadena.
    3. Establece el puntero de la cadena en `NULL`.

Comentarios:
    Facilita la gestión segura de la memoria para cadenas dinámicas.
*/

void	ft_free(void **str)
{
	if (*str)
		free(*str);
	*str = NULL;
}

/*
free_environment

Propósito:
    Libera toda la memoria asociada al entorno del shell.

Lógica:
    1. Llama a `free_env_lst` para liberar la lista de variables de entorno.
    2. Llama a `free_array` para liberar el array de entorno (`envp`).

Comentarios:
    Asegura la limpieza de las variables de entorno al cerrar el shell.
*/

void	free_environment(t_data *data)
{
	free_env_lst(data);
	free_array(&(data->envp));
}

/*
free_tokens

Propósito:
    Libera todos los tokens almacenados en la estructura de entrada.

Lógica:
    1. Recorre la lista de tokens en `data->input.tokens`.
    2. Libera la memoria de cada token y del nodo correspondiente.
    3. Inicializa cada nodo liberado a un estado vacío.

Comentarios:
    Gestiona la liberación de memoria utilizada por los tokens.
*/

void	free_tokens(t_data *data)
{
	t_token	*tmp;

	while (data->input.tokens)
	{
		free(data->input.tokens->token);
		tmp = data->input.tokens;
		data->input.tokens = data->input.tokens->next;
		free(tmp);
	}
}

/*
reset_var

Propósito:
    Reinicia los valores predeterminados de las variables de `t_data`.

Lógica:
    1. Establece todos los descriptores de archivos y pipes a `-1`.
    2. Resetea todos los contadores y banderas de la estructura a cero.
    3. Inicializa los valores a sus predeterminados para evitar errores.

Comentarios:
    Prepara la estructura `t_data` para reutilización o cierre limpio.
*/

static void	reset_var(t_data *data)
{
	data->fd[0] = -1;
	data->fd[1] = -1;
	data->l_pipe[0] = -1;
	data->l_pipe[1] = -1;
	data->r_pipe[0] = -1;
	data->r_pipe[1] = -1;
	data->in_cmd = 0;
	data->in_arg = 0;
	data->in_local = 0;
	data->n_cmd = 0;
	data->n_pipe = 0;
	data->n_files = 0;
	data->status = 0;
	data->exit_code = 0;
	data->heredoc = NULL;
	data->input = (t_input){0};
}

/*
free_data

Propósito:
    Libera todos los recursos asociados a la estructura principal `t_data`.

Lógica:
    1. Libera cadenas dinámicas como `raw_line`, `history`, y `cwd`.
    2. Libera listas como `tokens` y `commands`.
    3. Llama a `reset_var` para restablecer la estructura `t_data`.

Comentarios:
    Garantiza la liberación de memoria y la estabilidad del shell al cerrarlo.
*/

void	free_data(t_data *data)
{
	ft_free((void *)&(data->input.raw_line));
	ft_free((void *)&(data->history));
	ft_free((void *)&(data->cwd));
	ft_free((void *)&(data->prompt));
	free_array(&(data->paths));
	free_tokens(data);
	free_cmds(data);
	reset_var(data);
}

/*
Resumen del archivo

Propósito:
    Implementa funciones para liberar memoria y reiniciar estructuras.

Lógica:
    1. ft_free: Libera cadenas dinámicas.
    2. free_environment: Libera variables de entorno.
    3. free_tokens: Libera tokens de entrada.
    4. reset_var: Reinicia valores predeterminados en `t_data`.
    5. free_data: Libera todos los recursos asociados a `t_data`.

Comentarios:
    Este archivo asegura la correcta gestión y
	liberación de memoria para evitar fugas.
*/
