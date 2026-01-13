/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_later.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:32:03 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 11:56:17 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
replace_dollar_2

Propósito:
    Reemplaza un identificador `$` en una cadena con su valor correspondiente.

Lógica:
    1. Extrae el identificador usando `extract_id`.
    2. Obtiene el valor asociado al identificador con `get_dollar_value`.
    3. Reemplaza el identificador en la cadena con su valor usando `str_replace`.
    4. Libera memoria de las variables temporales.

Comentarios:
    Extiende la funcionalidad para manejar casos avanzados de expansión de `$`.
*/

static void	replace_dollar_2(t_data *data, char **new_term)
{
	char		*identifier;
	char		*value;
	char		*tmp;

	identifier = extract_id(*new_term);
	value = get_dollar_value(data, identifier + 1);
	tmp = *new_term;
	*new_term = str_replace(*new_term, identifier, value);
	free(identifier);
	free(tmp);
}

/*
seek_replace_2

Propósito:
    Busca y reemplaza variables `$` en una cadena,
	considerando contextos avanzados.

Lógica:
    1. Duplica la cadena de entrada como `new_term`.
    2. Busca el carácter `$` y verifica si es un identificador válido.
    3. Llama a `replace_dollar_2` para reemplazar el identificador con su valor.
    4. Itera hasta que todos los `$` hayan sido procesados.

Comentarios:
    Maneja reemplazos complejos de variables `$`
	en cadenas con varias condiciones.
*/

static char	*seek_replace_2(t_data *data, char *term, t_list *next)
{
	char	*new_term;
	char	*dollar;
	char	*next_to;

	new_term = ft_strdup(term);
	dollar = term;
	while (dollar)
	{
		dollar = ft_strchr(new_term, '$');
		if (dollar)
		{
			next_to = dollar + 1;
			if ((*next_to && \
			(*next_to == '$' || *next_to == '?' || valid_char(*next_to))) \
			|| (!(*next_to) && next))
				replace_dollar_2(data, &new_term);
			else
				dollar = NULL;
		}
	}
	return (new_term);
}

/*
expand_terms_2

Propósito:
    Expande todas las variables `$` en una lista de términos.

Lógica:
    1. Itera sobre la lista de términos.
    2. Ignora términos que comienzan con comillas simples.
    3. Llama a `seek_replace_2` para procesar cada término.
    4. Actualiza los términos en la lista con los resultados expandidos.

Comentarios:
    Procesa listas de términos para realizar expansiones avanzadas de variables.
*/

static void	expand_terms_2(t_data *data, t_list **lst)
{
	t_list	*head;
	char	*new_term;

	head = *lst;
	while ((*lst))
	{
		if (*(char *)(*lst)->content != '\'')
		{
			new_term = seek_replace_2(
					data, (char *)(*lst)->content, ((*lst)->next));
			free((*lst)->content);
			(*lst)->content = new_term;
		}
		(*lst) = (*lst)->next;
	}
	*lst = head;
}

/*
expand_later

Propósito:
    Expande variables `$` en una línea completa, segmentada por términos.

Lógica:
    1. Divide la línea en una lista de términos con `split_terms`.
    2. Llama a `expand_terms_2` para procesar las expansiones en la lista.
    3. Reensambla la lista de términos en una sola cadena.
    4. Libera memoria asociada a los términos originales.

Comentarios:
    Maneja expansiones de variables en líneas completas de entrada.
*/

void	expand_later(t_data *data, char **line)
{
	t_list	*lst;

	lst = split_terms(*line);
	expand_terms_2(data, &lst);
	free(*line);
	*line = lst_str_join(lst);
	free_lst(&lst);
}

/*
Resumen del archivo

Propósito:
    Gestiona expansiones avanzadas de variables `$` en líneas y términos
	de información recibida por heredoc.

Lógica:
    1. replace_dollar_2: Reemplaza identificadores `$` con valores.
    2. seek_replace_2: Busca y procesa reemplazos en cadenas.
    3. expand_terms_2: Expande variables `$` en listas de términos.
    4. expand_later: Maneja expansiones en líneas completas de entrada.

Comentarios:
    Este archivo implementa una expansión más detallada de variables para
    manejar casos complejos en el shell.
*/
