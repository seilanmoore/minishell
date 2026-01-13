/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checks1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:13:34 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 10:57:05 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
check_redirections

Propósito:
    Identifica tokens que representan redirecciones o pipes y asigna su tipo.

Lógica:
    1. Si el token no está entre comillas:
        - Identifica `|` como `PIPE`.
        - Identifica `<` como `LEFT` y `>` como `RIGHT`.
        - Identifica `<<` como `LEFTT` y `>>` como `RIGHTT`.
    2. Incrementa `n_pipe` si el token es `|`.
    3. Asigna el tipo correspondiente al token.

Comentarios:
    Clasifica tokens relacionados con redirecciones y pipes.
*/

static int	check_redirections(t_data *data, t_token *ptr, int i)
{
	if (ptr->quote != NO_QUOTE)
		return (0);
	if (ft_strlen(ptr->token) == 1)
	{
		if (ptr->token[0] == '|')
		{
			data->n_pipe++;
			data->in_cmd = 0;
			return (access_to_types(data, i, PIPE), 1);
		}
		else if (ptr->token[0] == '<')
			return (access_to_types(data, i, LEFT), 1);
		else if (ptr->token[0] == '>')
			return (access_to_types(data, i, RIGHT), 1);
	}
	else if (ft_strlen(ptr->token) == 2)
	{
		if (!ft_strcmp(ptr->token, ">>"))
			return (access_to_types(data, i, RIGHTT), 1);
		else if (!ft_strcmp(ptr->token, "<<"))
			return (access_to_types(data, i, LEFTT), 1);
	}
	return (0);
}

/*
check_files

Propósito:
    Verifica si un token representa un archivo en una redirección.

Lógica:
    1. Si el token anterior es `LEFTT`, asigna el tipo `HERE`.
    2. Si el token anterior es `LEFT`, `RIGHT` o `RIGHTT`, asigna `FILE`.
    3. Retorna 1 si el tipo se asigna, 0 en caso contrario.

Comentarios:
    Relaciona tokens con sus redirecciones correspondientes como archivos.
*/

static int	check_files(t_data *data, t_token *ptr, int i)
{
	if (ptr->prev)
	{
		if (ptr->prev->type == LEFTT)
			return (access_to_types(data, i, HERE), 1);
		if (ptr->prev->type == LEFT || \
		ptr->prev->type == RIGHT || \
		ptr->prev->type == RIGHTT)
			return (access_to_types(data, i, FILE), 1);
	}
	return (0);
}

/*
check_locals

Propósito:
    Identifica tokens relacionados con variables locales y sus valores.

Lógica:
    1. Si no hay un comando activo:
        - Identifica si el token anterior es `LOCAL` y finaliza con `=`.
        - Asigna `LOCAL_VAL` al token actual si es un valor.
        - Si contiene un `=`, asigna el tipo `LOCAL`.

Comentarios:
    Procesa declaraciones y asignaciones de variables locales.
*/

static int	check_locals(t_data *data, t_token *ptr, int i)
{
	t_token	*prev;
	int		prev_len;

	if (data->in_cmd)
		return (0);
	prev = ptr->prev;
	if (prev)
		prev_len = ft_strlen(prev->token);
	if (prev && prev->type == LOCAL && \
	prev->token[prev_len - 1] == '=' && prev->end_space == 0)
		return (access_to_types(data, i, LOCAL_VAL), 1);
	else if (ft_strchr(ptr->token, '='))
		return (access_to_types(data, i, LOCAL), 1);
	return (0);
}

/*
type_checks

Propósito:
    Determina el tipo de cada token mediante verificaciones específicas.

Lógica:
    1. Llama a `check_redirections` para identificar redirecciones o pipes.
    2. Llama a `check_files` para clasificar archivos.
    3. Llama a `check_locals` para identificar variables locales.
    4. Si ninguna de las anteriores aplica, verifica comandos con `check_cmds`.

Comentarios:
    Es el punto central para asignar tipos a tokens en el análisis.
*/

void	type_checks(t_data *data, t_token *ptr, int i)
{
	if (check_redirections(data, ptr, i))
		return ;
	if (check_files(data, ptr, i))
		return ;
	if (check_locals(data, ptr, i))
		return ;
	check_cmds(data, ptr, i);
}

/*
Resumen del archivo

Propósito:
    Clasifica y asigna tipos a tokens según su contexto en la entrada.

Lógica:
    1. check_redirections: Identifica redirecciones y pipes.
    2. check_files: Clasifica archivos en redirecciones.
    3. check_locals: Detecta variables locales y sus valores.
    4. type_checks: Integra todas las verificaciones de tipos.

Comentarios:
    Este archivo implementa las verificaciones detalladas necesarias
    para asignar tipos a tokens en el proceso de parseo.
*/
