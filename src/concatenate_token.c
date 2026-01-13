/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenate_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:21:13 by smoore-a          #+#    #+#             */
/*   Updated: 2025/01/20 22:30:45 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
concatenate

Propósito:
    Realiza la concatenación de una lista de tokens.

Lógica:
    1. Combina los valores de los tokens en una cadena completa.
    2. Utiliza un puntero temporal para manejar la memoria intermedia.
    3. Almacena el resultado concatenado en una nueva estructura de token.
    4. Actualiza la lista de tokens proporcionada.

Comentarios:
    Esta función es utilizada internamente para preparar datos
	antes de procesarlos
    en operaciones más amplias del programa.
*/

static void	concatenate(t_data *data, t_token **new_lst)
{
	char	*full_str;
	char	*tmp;

	full_str = ft_strdup(data->input.tokens->token);
	while (data->input.tokens->next && \
	!data->input.tokens->end_space)
	{
		tmp = full_str;
		full_str = ft_strjoin(full_str, data->input.tokens->next->token);
		data->input.tokens = data->input.tokens->next;
		free (tmp);
	}
	add_back_token(new_lst, new_token(\
	full_str, 0, data->input.tokens->quote, \
	data->input.tokens->end_space));
}

/*
concatenate_tokens

Propósito:
    Implementa la funcionalidad principal para concatenar todos los tokens
    de una lista específica dentro del contexto de `t_data`.

Lógica:
    1. Inicializa una nueva lista para almacenar los tokens concatenados.
    2. Itera sobre la lista original de tokens.
    3. Llama a `concatenate` para procesar cada grupo de tokens relacionados.
    4. Sustituye la lista original con la nueva lista concatenada.

Comentarios:
    Esta función es el punto de entrada principal para gestionar operaciones
    de concatenación a nivel global en el programa.
*/

void	concatenate_tokens(t_data *data)
{
	t_token	*new_lst;
	t_token	*head;

	new_lst = (t_token *){0};
	head = data->input.tokens;
	while (data->input.tokens)
	{
		concatenate(data, &(new_lst));
		data->input.tokens = data->input.tokens->next;
	}
	data->input.tokens = head;
	free_tokens(data);
	data->input.tokens = new_lst;
}

/*
Resumen del archivo

Propósito:
    Implementa la lógica de concatenación de tokens, facilitando el manejo
    de comandos y argumentos en el shell `minishell`.

Lógica:
    1. Define la función `concatenate` para unir valores de tokens
	en una cadena completa.
    2. Implementa `concatenate_tokens` como un punto de entrada principal:
        - Itera sobre una lista de tokens.
        - Utiliza `concatenate` para procesar grupos de tokens relacionados.
        - Reemplaza la lista original por una nueva lista concatenada.
    3. Prepara los tokens concatenados para ser utilizados
	en etapas posteriores del programa.

Comentarios:
    Este archivo organiza la lógica necesaria para procesar y unificar tokens,
    un paso crítico en el análisis y preparación de comandos en el shell.
*/
