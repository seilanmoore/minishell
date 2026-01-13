/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j_expand_terms.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:53:56 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 11:08:29 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
d_quote_term

Propósito:
    Maneja términos delimitados por comillas dobles y los agrega a una lista.

Lógica:
    1. Encuentra el inicio y el final del término entre comillas dobles.
    2. Extrae el término con `ft_substr` y lo agrega a la lista.
    3. Ajusta los índices para continuar el procesamiento.

Comentarios:
    Procesa términos entre comillas dobles, permitiendo caracteres especiales.
*/

static void	d_quote_term(t_list **lst, char *str, int *i, int *j)
{
	*j = *i;
	while (str[++(*i)] && str[*i] != '\"')
		;
	ft_lstadd_back(lst, ft_lstnew(ft_substr(str, *j, *i - *j + 1)));
	*j = *i + 1;
}

/*
s_quote_term

Propósito:
    Maneja términos delimitados por comillas simples y los agrega a una lista.

Lógica:
    1. Encuentra el inicio y el final del término entre comillas simples.
    2. Extrae el término con `ft_substr` y lo agrega a la lista.
    3. Ajusta los índices para continuar el procesamiento.

Comentarios:
    Procesa términos entre comillas simples, que se tratan literalmente.
*/

static void	s_quote_term(t_list **lst, char *str, int *i, int *j)
{
	*j = *i;
	while (str[++(*i)] && str[*i] != '\'')
		;
	ft_lstadd_back(lst, ft_lstnew(ft_substr(str, *j, *i - *j + 1)));
	*j = *i + 1;
}

/*
dollar_term

Propósito:
    Procesa términos relacionados con el carácter `$` y los agrega a una lista.

Lógica:
    1. Si el siguiente carácter es `$` o `?`, extrae ambos y los agrega.
    2. Si no, extrae hasta encontrar otro `$`, comilla o carácter especial.
    3. Ajusta los índices y agrega el término a la lista.

Comentarios:
    Detecta variables y códigos especiales asociados al carácter `$`.
*/

static void	dollar_term(t_list **lst, char *str, int *i, int *j)
{
	*j = *i;
	if (str[(*i) + 1] && \
	(str[(*i) + 1] == '$' || str[(*i) + 1] == '?'))
	{
		ft_lstadd_back(lst, ft_lstnew(ft_substr(str, *j, 2)));
		(*i)++;
		*j = *i + 1;
	}
	else
	{
		while (str[++(*i)] && str[*i] != '$' && \
		str[*i] != '\'' && str[*i] != '\"')
			;
		ft_lstadd_back(lst, ft_lstnew(ft_substr(str, *j, *i - *j)));
		if (str[*i])
			(*i)--;
		*j = *i;
	}
}

/*
add_terms

Propósito:
    Identifica el tipo de término y llama a la función correspondiente.

Lógica:
    1. Determina el delimitador actual (`'`, `"`, `$`).
    2. Llama a `s_quote_term`, `d_quote_term` o `dollar_term` según corresponda.
    3. Si no hay delimitador especial, agrega el término directamente.

Comentarios:
    Es la función central para identificar y procesar términos.
*/

static void	add_terms(t_list **lst, char *str, int *i, int *j)
{
	if (str[*i] == '\'')
		s_quote_term(lst, str, i, j);
	else if (str[*i] == '\"')
		d_quote_term(lst, str, i, j);
	else if (str[*i] == '$')
		dollar_term(lst, str, i, j);
	else if (!str[*i + 1] || (str[*i + 1] && \
	(str[*i + 1] == '\'' || str[*i + 1] == '\"' || str[*i + 1] == '$')))
		ft_lstadd_back(lst, ft_lstnew(ft_substr(str, *j, *i - *j + 1)));
	if (str[*i])
		(*i)++;
}

/*
split_terms

Propósito:
    Divide una línea en términos basados en comillas y `$`.

Lógica:
    1. Inicializa una lista vacía.
    2. Itera sobre la línea, llamando a `add_terms` para dividir los términos.
    3. Retorna la lista con los términos procesados.

Comentarios:
    Convierte una línea en una lista de términos segmentados por delimitadores.
*/

t_list	*split_terms(char *line)
{
	t_list	*lst;
	int		i;
	int		start;

	i = 0;
	start = 0;
	lst = NULL;
	while (line[i])
		add_terms(&lst, line, &i, &start);
	return (lst);
}

/*
Resumen del archivo

Propósito:
    Divide una línea de entrada en términos manejables basados en delimitadores.

Lógica:
    1. d_quote_term: Maneja términos entre comillas dobles.
    2. s_quote_term: Maneja términos entre comillas simples.
    3. dollar_term: Procesa términos relacionados con `$`.
    4. add_terms: Identifica y delega el procesamiento de términos.
    5. split_terms: Convierte una línea en una lista de términos procesados.

Comentarios:
    Este archivo maneja la segmentación avanzada de entradas para su análisis.
*/
