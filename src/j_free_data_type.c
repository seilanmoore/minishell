/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j_free_data_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:02:07 by smoore-a          #+#    #+#             */
/*   Updated: 2025/01/20 20:25:50 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
free_array

Propósito:
    Libera la memoria de un array de cadenas y lo inicializa a NULL.

Lógica:
    1. Itera sobre el array, liberando cada cadena.
    2. Libera la memoria del array en sí.
    3. Asigna `NULL` al puntero del array.

Comentarios:
    Evita fugas de memoria al liberar arrays dinámicos.
*/

void	free_array(char ***array)
{
	int	i;

	i = -1;
	if (!(*array))
		return ;
	while ((*array)[++i])
	{
		free((*array)[i]);
		(*array)[i] = NULL;
	}
	free(*array);
	*array = NULL;
}

/*
free_local

Propósito:
    Libera todas las variables locales en la lista `locals` de `data`.

Lógica:
    1. Itera sobre la lista de variables locales.
    2. Libera el nombre y valor de cada variable.
    3. Libera la memoria del nodo y avanza al siguiente.

Comentarios:
    Limpia la lista de variables locales al cerrar el shell.
*/

void	free_local(t_data *data)
{
	t_env	*tmp;

	while (data->locals)
	{
		ft_free((void *)&(data->locals->variable));
		ft_free((void *)&(data->locals->value));
		tmp = data->locals;
		data->locals = data->locals->next;
		*tmp = (t_env){0};
		free(tmp);
	}
}

/*
free_env_lst

Propósito:
    Libera todas las variables de entorno en la lista `env` de `data`.

Lógica:
    1. Itera sobre la lista de variables de entorno.
    2. Libera el nombre y valor de cada variable.
    3. Libera la memoria del nodo y avanza al siguiente.

Comentarios:
    Garantiza la limpieza de la lista de entorno al liberar memoria.
*/

void	free_env_lst(t_data *data)
{
	t_env	*tmp;

	while (data->env)
	{
		ft_free((void *)&(data->env->variable));
		ft_free((void *)&(data->env->value));
		tmp = data->env;
		data->env = data->env->next;
		*tmp = (t_env){0};
		free(tmp);
	}
}

/*
free_cmds

Propósito:
    Libera todos los comandos en la lista de `data->input.command`.

Lógica:
    1. Itera sobre la lista de comandos.
    2. Libera el comando, sus argumentos y el nodo completo.
    3. Asigna `NULL` al nodo tras liberarlo.

Comentarios:
    Limpia la lista de comandos después de su ejecución.
*/

void	free_cmds(t_data *data)
{
	t_cmd	*tmp;

	while (data->input.command)
	{
		ft_free((void *)&(data->input.command->cmd));
		free_array(&(data->input.command->args));
		tmp = data->input.command;
		data->input.command = data->input.command->next;
		*tmp = (t_cmd){0};
		free(tmp);
	}
}

/*
free_lst

Propósito:
    Libera todos los nodos de una lista genérica y sus contenidos.

Lógica:
    1. Itera sobre la lista, liberando el contenido de cada nodo.
    2. Libera el nodo y avanza al siguiente.
    3. Inicializa el puntero de la lista a `NULL`.

Comentarios:
    Maneja la liberación de listas genéricas usadas en el shell.
*/

void	free_lst(t_list **lst)
{
	t_list	*tmp;

	while (*lst)
	{
		tmp = *lst;
		free((*lst)->content);
		(*lst)->content = NULL;
		*lst = (*lst)->next;
		free(tmp);
	}
	free(*lst);
	*lst = NULL;
}

/*
Resumen del archivo

Propósito:
    Proporciona funciones para liberar memoria de estructuras y listas.

Lógica:
    1. free_array: Libera arrays dinámicos de cadenas.
    2. free_local: Libera variables locales en `locals`.
    3. free_env_lst: Libera la lista de variables de entorno en `env`.
    4. free_cmds: Libera la lista de comandos en `input.command`.
    5. free_lst: Libera nodos y contenidos de listas genéricas.

Comentarios:
    Este archivo asegura la limpieza de estructuras dinámicas para evitar
    fugas de memoria en el shell.
*/
