/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:15:54 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 10:53:57 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
assign_opt_arg

Propósito:
    Asigna opciones y argumentos a cada comando en la lista de tokens.

Lógica:
    1. Recorre los tokens buscando comandos (`type == CMD`).
    2. Para cada comando, identifica el primer token de tipo `OPTION` y lo
       asigna al campo `opt`.
    3. Identifica el primer token de tipo `ARG` y lo asigna al campo `arg`.
    4. Continúa hasta encontrar un `PIPE` o el final de la lista.

Comentarios:
    Relaciona cada comando con sus opciones y argumentos.
*/

void	assign_opt_arg(t_data *data)
{
	t_token	*tmp;
	t_token	*aux;

	tmp = data->input.tokens;
	while (tmp)
	{
		if (tmp->type == CMD)
		{
			aux = tmp->next;
			while (aux && aux->type != PIPE)
			{
				if (aux->type == OPTION && !tmp->opt)
					tmp->opt = aux;
				else if (aux->type == ARG && !tmp->arg)
					tmp->arg = aux;
				aux = aux->next;
			}
		}
		tmp = tmp->next;
	}
}

/*
access_to_types

Propósito:
    Asigna un tipo específico a un token en una posición determinada.

Lógica:
    1. Recorre la lista de tokens hasta llegar a la posición `target`.
    2. Asigna el tipo `type` al token correspondiente.
    3. Restaura el puntero al inicio de la lista.

Comentarios:
    Permite modificar dinámicamente el tipo de un token específico.
*/

void	access_to_types(t_data *data, int target, int type)
{
	t_token	*head;
	int		i;

	head = data->input.tokens;
	i = -1;
	while (++i != target)
		data->input.tokens = data->input.tokens->next;
	if (data->input.tokens)
		data->input.tokens->type = type;
	data->input.tokens = head;
}

/*
assign_types

Propósito:
    Determina y asigna el tipo correspondiente a cada token.

Lógica:
    1. Configura los enlaces previos de los tokens con `set_prev_token`.
    2. Recorre la lista de tokens.
    3. Para cada token, invoca `type_checks` para determinar su tipo.
    4. Actualiza los tipos según los resultados de `type_checks`.

Comentarios:
    Organiza la asignación de tipos para su uso posterior en el análisis.
*/

void	assign_types(t_data	*data)
{
	t_token	*ptr;
	int		i;

	set_prev_token(data);
	ptr = data->input.tokens;
	i = 0;
	while (ptr)
	{
		type_checks(data, ptr, i);
		ptr = ptr->next;
		i++;
	}
}

/*
Resumen del archivo

Propósito:
    Gestiona la asignación de tipos y relaciones entre tokens.

Lógica:
    1. assign_opt_arg: Relaciona comandos con sus opciones y argumentos.
    2. access_to_types: Cambia el tipo de un token específico.
    3. assign_types: Determina los tipos de todos los tokens.

Comentarios:
    Este archivo organiza los tokens para el análisis semántico posterior.
*/
