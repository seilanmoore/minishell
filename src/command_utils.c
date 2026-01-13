/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:52:01 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 11:01:24 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
last_cmd

Propósito:
    Obtiene el último comando en una lista de comandos.

Lógica:
    1. Si la lista está vacía, retorna `NULL`.
    2. Recorre la lista de comandos hasta que `next` sea `NULL`.
    3. Retorna el nodo actual como el último comando.

Comentarios:
    Es útil para agregar nuevos comandos al final de la lista.
*/

t_cmd	*last_cmd(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/*
add_back_cmd

Propósito:
    Añade un nuevo comando al final de una lista de comandos.

Lógica:
    1. Si la lista ya tiene elementos, usa `last_cmd` para encontrar el último.
    2. Conecta el nuevo comando al final de la lista.
    3. Si la lista está vacía, inicializa el nodo como primer elemento.

Comentarios:
    Permite construir dinámicamente la lista de comandos.
*/

void	add_back_cmd(t_cmd **lst, t_cmd *node)
{
	if (lst && node)
	{
		if (*lst)
			last_cmd(*lst)->next = node;
		else
			*lst = node;
	}
}

/*
new_cmd

Propósito:
    Crea un nuevo nodo de comando con sus argumentos y tipo.

Lógica:
    1. Reserva memoria para el nodo de comando.
    2. Copia el nombre del comando desde el token.
    3. Asigna el array de argumentos y el indicador de si es interno.
    4. Asocia el token al comando.
    5. Retorna el nodo creado o `NULL` en caso de error.

Comentarios:
    Construye nodos de comando que se usarán en la lista de ejecución.
*/

t_cmd	*new_cmd(t_token *token, char **arguments, int builtin)
{
	t_cmd	*new_node;

	if (!token)
		return (NULL);
	new_node = malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	new_node->cmd = ft_strdup(token->token);
	if (!(new_node->cmd))
	{
		free(new_node);
		return (NULL);
	}
	new_node->args = arguments;
	new_node->builtin = builtin;
	new_node->token = token;
	return (new_node);
}

/*
Resumen del archivo

Propósito:
    Proporciona utilidades para gestionar listas de comandos.

Lógica:
    1. last_cmd: Encuentra el último comando en la lista.
    2. add_back_cmd: Añade un nuevo comando al final de la lista.
    3. new_cmd: Crea un nodo de comando con sus datos y configuración.

Comentarios:
    Facilita la creación y gestión de estructuras de comandos en el shell.
*/
