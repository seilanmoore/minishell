/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:03:30 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 10:29:02 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
end_space

Propósito: Determina si el token actual termina con un espacio o con un
carácter especial.

Lógica:

    Itera sobre los caracteres en la posición actual (aux1).
    Ignora comillas (' o "), verificando si están correctamente balanceadas.
    Si encuentra un espacio o un carácter no alfabético (no_word),
	devuelve 1 (indica que hay un espacio al final).
    En caso contrario, devuelve 0.

Comentarios: Es crucial para manejar cómo los tokens interactúan entre sí en
función de su delimitador.
*/

int	end_space(t_var *var)
{
	char	*quotes;

	quotes = &(var->aux1[var->i]);
	while (*quotes && (*quotes == '\'' || *quotes == '\"'))
	{
		if (*quotes == '\'')
		{
			if (*(++quotes) == '\'')
				quotes++;
			else
				return (0);
		}
		else if (*quotes == '\"')
		{
			if (*(++quotes) == '\"')
				quotes++;
			else
				return (0);
		}
	}
	if (is_space(*quotes) || no_word(*quotes))
		return (1);
	return (0);
}

/*
set_prev_token

Propósito: Configura un puntero al token anterior para cada elemento en
la lista de tokens.

Lógica:

    Itera a través de la lista de tokens en data->input.tokens.
    Asigna el token previo (prev) al actual mientras avanza en la lista.

Comentarios: Esto es útil para analizar la relación entre tokens
consecutivos (por ejemplo, operadores y argumentos).
*/

void	set_prev_token(t_data *data)
{
	t_token	*head;
	t_token	*prev;

	head = data->input.tokens;
	prev = head;
	if (!data->input.tokens)
		return ;
	data->input.tokens = data->input.tokens->next;
	while (data->input.tokens)
	{
		data->input.tokens->prev = prev;
		prev = data->input.tokens;
		data->input.tokens = data->input.tokens->next;
	}
	data->input.tokens = head;
}

/*
last_token

Propósito: Encuentra el último token de una lista de tokens.

Lógica:

    Recorre la lista hasta que el siguiente nodo sea NULL.
    Devuelve el nodo actual.

Comentarios: Es una función auxiliar para operar sobre
listas enlazadas de tokens.
*/

t_token	*last_token(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/*
add_back_token

Propósito: Añade un nuevo token al final de una lista enlazada.

Lógica:

    Si la lista ya tiene elementos, conecta el nuevo token al final.
    Si está vacía, inicializa la lista con el nuevo token.

Comentarios: Permite agregar dinámicamente nuevos tokens generados
durante el proceso de tokenización.
*/

void	add_back_token(t_token **lst, t_token *node)
{
	if (lst && node)
	{
		if (*lst)
			last_token(*lst)->next = node;
		else
			*lst = node;
	}
}

/*
new_token

Propósito: Crea un nuevo nodo de tipo t_token.

Lógica:

    Reserva memoria para el nuevo nodo.
    Inicializa los campos:
        token: Contenido textual.
        type: Tipo del token (por ejemplo, palabra, operador, etc.).
        quote: Indica si está entre comillas simples o dobles.
        end_space: Si termina con un espacio.
        Otros campos (opt, arg, prev, next) se inicializan a NULL.

Comentarios: Es la función base para crear un token que luego
será añadido a la lista.
*/

t_token	*new_token(void *token, int type, int quote, int end_space)
{
	t_token	*new_node;

	if (!token)
		return (NULL);
	new_node = (t_token *)malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->token = token;
	new_node->type = type;
	new_node->quote = quote;
	new_node->end_space = end_space;
	new_node->opt = NULL;
	new_node->arg = NULL;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

/*
tokenizer_utils.c contiene herramientas auxiliares para:

    Evaluar si un token termina con un espacio (end_space).
    Operar sobre listas de tokens:
        Crear (new_token).
        Agregar al final (add_back_token).
        Obtener el último (last_token).
        Configurar relaciones entre nodos (set_prev_token).

Estas funciones refuerzan el flujo de tokenización definido en tokenizer.c.
*/