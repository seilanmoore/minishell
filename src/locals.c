/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locals.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:56:20 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 11:16:23 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
mod_env_value

Propósito:
    Modifica el valor de una variable en la lista de entorno.

Lógica:
    1. Libera el valor actual del nodo.
    2. Asigna el nuevo valor proporcionado o una cadena vacía si es nulo.

Comentarios:
    Actualiza dinámicamente los valores de variables en el entorno.
*/

static void	mod_env_value(t_env *node, char *value)
{
	if (node)
	{
		free(node->value);
		if (value)
			node->value = ft_strdup(value);
		else
			node->value = ft_strdup("");
	}
}

/*
get_loc_var

Propósito:
    Busca una variable local específica en la lista de variables locales.

Lógica:
    1. Itera sobre la lista `locals`.
    2. Compara el nombre de cada variable con `variable` usando `ft_strcmp`.
    3. Retorna el nodo si encuentra coincidencia; `NULL` en caso contrario.

Comentarios:
    Facilita la búsqueda de variables locales en el entorno.
*/

static t_env	*get_loc_var(t_env *locals, char *variable)
{
	while (locals)
	{
		if (!ft_strcmp(locals->variable, variable))
			return (locals);
		locals = locals->next;
	}
	return (locals);
}

/*
mod_loc_value

Propósito:
    Modifica o crea el valor de una variable local.

Lógica:
    1. Si el nodo ya existe, actualiza su valor.
    2. Si no existe, crea una nueva variable con `var` y `val`.
    3. Agrega la nueva variable al final de la lista.

Comentarios:
    Gestiona la actualización o adición de variables locales.
*/

static void	mod_loc_value(t_env **lst, t_env *node, char *var, char *val)
{
	if (node)
	{
		free(node->value);
		if (val)
			node->value = ft_strdup(val);
		else
			node->value = ft_strdup("");
	}
	else
	{
		if (val)
			add_back_variable(lst, new_variable(var, val));
		else
			add_back_variable(lst, new_variable(var, ""));
	}
}

/*
add_local

Propósito:
    Añade una nueva variable local a las listas de entorno y locales.

Lógica:
    1. Divide el token en nombre (`variable`) y valor (`equal`).
    2. Verifica errores de identificación con `id_error`.
    3. Si es válida, actualiza la variable en `env` y `locals`.
    4. Retorna 1 si se agregó correctamente, 0 en caso de error.

Comentarios:
    Integra variables locales en el entorno del shell.
*/

static int	add_local(t_data *data, char *token)
{
	t_env	*node;
	char	*variable;
	char	*equal;

	variable = NULL;
	equal = ft_strchr(token, '=');
	if (equal)
		variable = ft_substr(token, 0, equal - token);
	if (id_error(data, token, variable, 0))
	{
		free(variable);
		return (0);
	}
	if (variable)
	{
		node = get_env_var(data->env, variable);
		mod_env_value(node, equal + 1);
		node = get_loc_var(data->locals, variable);
		mod_loc_value(&(data->locals), node, variable, equal + 1);
		free(variable);
	}
	return (1);
}

/*
locals

Propósito:
    Procesa y actualiza las variables locales en los tokens de entrada.

Lógica:
    1. Recorre los tokens en busca de aquellos marcados como `LOCAL`.
    2. Llama a `add_local` para agregar o actualizar las variables.
    3. Si hubo cambios, sincroniza el entorno con `upd_env`.
    4. Retorna 127 si hubo errores; 0 en caso de éxito.

Comentarios:
    Maneja las operaciones principales relacionadas con variables locales.
*/

int	locals(t_data *data)
{
	t_token	*tmp;
	int		update;
	int		fail;

	fail = 0;
	update = 0;
	tmp = data->input.tokens;
	while (tmp)
	{
		if (tmp->type == LOCAL)
		{
			if (add_local(data, tmp->token) == 1)
				update = 1;
			else
				fail = 1;
		}
		tmp = tmp->next;
	}
	if (update)
		upd_env(data);
	if (fail)
		return (127);
	return (0);
}

/*
Resumen del archivo

Propósito:
    Gestiona la creación, actualización y sincronización de variables locales.

Lógica:
    1. mod_env_value: Modifica valores en la lista de entorno.
    2. get_loc_var: Busca variables locales en la lista.
    3. mod_loc_value: Modifica o crea variables locales.
    4. add_local: Añade variables locales al entorno y lista local.
    5. locals: Procesa y actualiza variables locales desde los tokens.

Comentarios:
    Este archivo centraliza la lógica para gestionar variables locales
    en el shell.
*/
