/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:17:10 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 10:52:52 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
parser

Propósito:
    Coordina las etapas del análisis y procesamiento de la línea de entrada.

Lógica:
    1. Convierte el entorno en una lista con `envp_to_lst`.
    2. Realiza la expansión de variables con `expand`.
    3. Tokeniza la entrada con `tokenizer`.
    4. Combina tokens relacionados con `concatenate_tokens`.
    5. Asigna tipos a los tokens con `assign_types`.
    6. Identifica opciones y argumentos con `assign_opt_arg`.
    7. Analiza comandos y opciones con `parse_cmd_opt`.
    8. Gestiona variables locales con `locals` y actualiza `exit_code`.

Comentarios:
    Centraliza las fases principales del análisis de la entrada del shell.
*/

void	parser(t_data *data)
{
	envp_to_lst(data);
	expand(data);
	tokenizer(data);
	concatenate_tokens(data);
	assign_types(data);
	assign_opt_arg(data);
	parse_cmd_opt(data);
	data->exit_code = locals(data);
}

/*
Resumen del archivo

Propósito:
    Implementa el flujo principal del análisis y procesamiento de entrada.

Lógica:
    1. Convierte el entorno en una lista con `envp_to_lst`.
    2. Expande variables, tokeniza y concatena tokens relacionados.
    3. Asigna tipos y argumentos a los tokens.
    4. Realiza el análisis semántico de comandos y opciones.

Comentarios:
    Este archivo organiza las etapas necesarias para preparar la entrada
    para su ejecución en el shell.
*/
