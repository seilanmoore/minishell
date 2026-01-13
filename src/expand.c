/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:53:56 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 13:28:29 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
replace_dollar

Propósito:
    Reemplaza una variable `$` en un término con su valor correspondiente.

Lógica:
    1. Extrae el identificador con `extract_id`.
    2. Obtiene el valor asociado usando `get_dollar_value`.
    3. Reemplaza el identificador en la cadena usando `str_replace`.
    4. Libera memoria de variables temporales usadas.

Comentarios:
    Implementa la expansión de variables `$` en una cadena específica.
*/

void	replace_dollar(t_data *data, char **new_term)
{
	char		*identifier;
	char		*value;
	char		*value_quoted;
	char		*tmp;

	identifier = extract_id(*new_term);
	value = ft_strjoin("\"", get_dollar_value(data, identifier + 1));
	value_quoted = ft_strjoin(value, "\"");
	free(value);
	tmp = *new_term;
	*new_term = str_replace(*new_term, identifier, value_quoted);
	free(identifier);
	free(tmp);
	free(value_quoted);
}

/*
seek_replace

Propósito:
    Busca y reemplaza variables `$` dentro de una cadena.

Lógica:
    1. Duplica la cadena original.
    2. Itera buscando el carácter `$` con `ft_strchr`.
    3. Llama a `replace_dollar` si encuentra variables válidas.
    4. Finaliza cuando no quedan más identificadores.

Comentarios:
    Expande todas las variables `$` presentes en una cadena dada.
*/

char	*seek_replace(t_data *data, char *term, t_list *next)
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
				replace_dollar(data, &new_term);
			else
				dollar = NULL;
		}
	}
	return (new_term);
}

/*
expand_terms

Propósito:
    Expande las variables `$` en cada nodo de una lista enlazada.

Lógica:
    1. Recorre la lista enlazada de términos.
    2. Si el término no está entre comillas simples, aplica `seek_replace`.
    3. Actualiza cada nodo con su versión expandida.

Comentarios:
    Permite la expansión de variables en toda la lista de términos.
*/

void	expand_terms(t_data *data, t_list **lst)
{
	t_list	*head;
	char	*new_term;

	head = *lst;
	while ((*lst))
	{
		if (*(char *)(*lst)->content != '\'')
		{
			new_term = seek_replace(
					data, (char *)(*lst)->content, ((*lst)->next));
			free((*lst)->content);
			(*lst)->content = new_term;
		}
		(*lst) = (*lst)->next;
	}
	*lst = head;
}

/*
lst_str_join

Propósito:
    Une los elementos de una lista enlazada en una sola cadena.

Lógica:
    1. Inicializa con el contenido del primer nodo.
    2. Itera sobre la lista, concatenando cada nodo al resultado acumulado.
    3. Retorna la cadena combinada.

Comentarios:
    Convierte una lista de términos en una cadena única.
*/

char	*lst_str_join(t_list *lst)
{
	char	*joined;
	char	*tmp;

	joined = ft_strdup((char *)lst->content);
	lst = lst->next;
	while (lst)
	{
		tmp = joined;
		joined = ft_strjoin(joined, (char *)lst->content);
		free(tmp);
		lst = lst->next;
	}
	return (joined);
}

/*
expand

Propósito:
    Realiza la expansión completa de variables en la línea de entrada.

Lógica:
    1. Divide la línea de entrada en términos con `split_terms`.
    2. Aplica `expand_terms` para realizar la expansión.
    3. Reconstruye la línea expandida con `lst_str_join`.
    4. Libera los recursos temporales usados.

Comentarios:
    Es la función principal de expansión, integrando todas las fases.
*/

void	expand(t_data *data)
{
	t_list	*lst;

	lst = split_terms(data->input.raw_line);
	expand_terms(data, &lst);
	free(data->input.raw_line);
	data->input.raw_line = lst_str_join(lst);
	free_lst(&lst);
}

/*
Resumen del archivo

Propósito:
    Implementa la expansión de variables como `$VAR`, `$$`, y `?$` en
    la línea de entrada.

Lógica:
    1. replace_dollar: Expande variables en cadenas específicas.
    2. seek_replace: Busca y expande variables en cadenas.
    3. expand_terms: Expande variables en listas de términos.
    4. lst_str_join: Reconstruye la línea de entrada expandida.
    5. expand: Coordina todo el proceso de expansión.

Comentarios:
    Este archivo maneja la expansión de variables en el shell.
*/
