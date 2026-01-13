/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:03:30 by smoore-a          #+#    #+#             */
/*   Updated: 2025/01/20 20:25:02 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
print_env

Propósito:
    Imprime todas las variables de entorno y sus valores.

Lógica:
    1. Recorre la lista de variables de entorno (`env`).
    2. Imprime el nombre y valor de cada variable en formato "VARIABLE: VALUE".
    3. Restaura el puntero de la lista al inicio.

Comentarios:
    Proporciona una visualización detallada del entorno para depuración.
*/

void	print_env(t_data *data)
{
	void	*head;

	head = data->env;
	while (data->env)
	{
		printf("VARIABLE: \'%s\'\nVALUE: \'%s\'\n", \
		data->env->variable, data->env->value);
		data->env = data->env->next;
	}
	data->env = head;
}

/*
del_node

Propósito:
    Elimina un nodo de la lista de entorno y libera su memoria.

Lógica:
    1. Libera la memoria de `variable` y `value` en el nodo.
    2. Libera el nodo y asigna `NULL` al puntero que lo contenía.

Comentarios:
    Es una función auxiliar para eliminar nodos de `t_env`.
*/

static void	del_node(t_env **lst, t_env *node)
{
	ft_free((void *)&(node->variable));
	ft_free((void *)&(node->value));
	free(node);
	*lst = NULL;
}

/*
del_env

Propósito:
    Elimina una variable específica de la lista de entorno.

Lógica:
    1. Recorre la lista buscando el nodo con el nombre de la variable.
    2. Si lo encuentra, ajusta los punteros para saltarlo y
	lo elimina con `del_node`.
    3. Restaura la lista al estado inicial tras la eliminación.

Comentarios:
    Permite eliminar variables de entorno de forma segura.
*/

void	del_env(t_env **env, char *variable)
{
	t_env	*head;
	t_env	*current;

	head = *env;
	current = (*env)->next;
	if (!current)
	{
		del_node(env, head);
		return ;
	}
	while (current)
	{
		if (!ft_strcmp(current->variable, variable))
		{
			(*env)->next = current->next;
			del_node(&(current), current);
		}
		else
		{
			*env = (*env)->next;
			current = current->next;
		}
	}
	*env = head;
}

/*
variable_len

Propósito:
    Calcula la longitud del nombre de una variable en una cadena `KEY=VALUE`.

Lógica:
    1. Itera sobre la cadena hasta encontrar el carácter `=`.
    2. Retorna la posición del carácter `=` como longitud.

Comentarios:
    Es útil para separar claves y valores en variables de entorno.
*/

int	variable_len(char *envp_line)
{
	int	i;

	i = -1;
	if (!envp_line)
		return (0);
	while (envp_line[++i] != '=')
		;
	return (i);
}

/*
get_env_var

Propósito:
    Busca una variable en la lista de entorno por su nombre.

Lógica:
    1. Itera sobre la lista de entorno.
    2. Compara el nombre de cada variable con `variable` usando `ft_strcmp`.
    3. Retorna el nodo si encuentra coincidencia; `NULL` en caso contrario.

Comentarios:
    Facilita la obtención de valores asociados a variables específicas.
*/

t_env	*get_env_var(t_env *env, char *variable)
{
	t_env	*head;

	if (!env || !variable)
		return (NULL);
	head = env;
	while (env)
	{
		if (!ft_strcmp(env->variable, variable))
			return (env);
		env = env->next;
	}
	env = head;
	return (NULL);
}

/*
Resumen del archivo

Propósito:
    Proporciona utilidades para manipular y consultar variables de entorno.

Lógica:
    1. print_env: Imprime las variables de entorno.
    2. del_node: Elimina un nodo de la lista de entorno.
    3. del_env: Elimina una variable de la lista de entorno.
    4. variable_len: Calcula la longitud del nombre de una variable.
    5. get_env_var: Busca y obtiene un nodo de variable por nombre.

Comentarios:
    Este archivo centraliza operaciones sobre la lista de variables de entorno.
*/
