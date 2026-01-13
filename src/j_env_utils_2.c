/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j_env_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:03:30 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 11:10:21 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
new_variable

Propósito:
    Crea un nuevo nodo de variable de entorno.

Lógica:
    1. Reserva memoria para un nodo de tipo `t_env`.
    2. Copia el nombre de la variable con `ft_strdup`.
    3. Si hay un valor, lo copia; de lo contrario, asigna una cadena vacía.
    4. Inicializa `next` a `NULL`.

Comentarios:
    Se utiliza para añadir nuevas variables al entorno.
*/

t_env	*new_variable(char *variable, char *value)
{
	t_env	*new_node;

	if (!variable)
		return (NULL);
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->variable = ft_strdup(variable);
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = ft_strdup("");
	new_node->next = NULL;
	return (new_node);
}

/*
last_variable

Propósito:
    Obtiene el último nodo de una lista de variables de entorno.

Lógica:
    1. Si la lista está vacía, retorna `NULL`.
    2. Recorre la lista hasta encontrar el último nodo (`next == NULL`).
    3. Retorna el último nodo encontrado.

Comentarios:
    Es útil para añadir nuevos nodos al final de la lista.
*/

t_env	*last_variable(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/*
add_back_variable

Propósito:
    Añade un nuevo nodo de variable al final de una lista de variables.

Lógica:
    1. Si la lista ya tiene elementos, usa `last_variable`
	para encontrar el final.
    2. Conecta el nuevo nodo al final de la lista.
    3. Si la lista está vacía, inicializa el nodo como el primer elemento.

Comentarios:
    Facilita la construcción dinámica de la lista de variables.
*/

void	add_back_variable(t_env **lst, t_env *node)
{
	if (lst && node)
	{
		if (*lst)
			last_variable(*lst)->next = node;
		else
			*lst = node;
	}
}

/*
env_size

Propósito:
    Calcula el número de elementos en una lista de variables de entorno.

Lógica:
    1. Inicializa un contador en 0.
    2. Recorre la lista, incrementando el contador por cada nodo.
    3. Retorna el tamaño de la lista.

Comentarios:
    Es útil para manejar operaciones que dependen del tamaño de la lista.
*/

int	env_size(t_env *lst)
{
	int	lst_len;

	lst_len = 0;
	while (lst)
	{
		lst = lst->next;
		lst_len++;
	}
	return (lst_len);
}

/*
upd_env

Propósito:
    Actualiza el array de variables de entorno a partir de la lista de `t_env`.

Lógica:
    1. Libera el array actual de variables de entorno (`envp`).
    2. Reconstruye el array desde la lista con `envp_to_array`.

Comentarios:
    Sincroniza la lista de entorno con su representación en array.
*/

void	upd_env(t_data *data)
{
	free_array(&(data->envp));
	envp_to_array(data);
}

/*
Resumen del archivo

Propósito:
    Proporciona utilidades para gestionar la lista de variables de entorno.

Lógica:
    1. new_variable: Crea un nuevo nodo de variable de entorno.
    2. last_variable: Obtiene el último nodo de la lista.
    3. add_back_variable: Añade un nodo al final de la lista.
    4. env_size: Calcula el tamaño de la lista de variables.
    5. upd_env: Sincroniza la lista de entorno con su array.

Comentarios:
    Este archivo facilita la gestión dinámica de variables de entorno
	en el shell.
*/
