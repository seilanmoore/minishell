/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j_bool_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:54:56 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 11:12:34 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
valid_char

Propósito:
    Verifica si un carácter es válido para un identificador.

Lógica:
    1. Retorna 0 si el carácter es nulo.
    2. Acepta letras (mayúsculas o minúsculas), números y el carácter `_`.
    3. Retorna 0 para cualquier otro carácter.

Comentarios:
    Útil para validar identificadores de variables o nombres.
*/

int	valid_char(char c)
{
	if (!c)
		return (0);
	if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z') && \
	(c < '0' || c > '9') && c != '_')
		return (0);
	return (1);
}

/*
no_word

Propósito:
    Verifica si un carácter corresponde a un operador especial.

Lógica:
    1. Retorna 1 si el carácter es `<`, `>` o `|`.
    2. Retorna 0 en caso contrario.

Comentarios:
    Diferencia operadores especiales de palabras regulares.
*/

int	no_word(int c)
{
	if (c == '<' || \
	c == '>' || \
	c == '|')
		return (1);
	return (0);
}

/*
is_redir

Propósito:
    Verifica si un tipo corresponde a una redirección.

Lógica:
    1. Retorna 1 si el tipo es `LEFT`, `LEFTT`, `RIGHT` o `RIGHTT`.
    2. Retorna 0 en caso contrario.

Comentarios:
    Facilita la identificación de tokens relacionados con redirecciones.
*/

int	is_redir(int c)
{
	if (c == LEFT || \
	c == LEFTT || \
	c == RIGHT || \
	c == RIGHTT)
		return (1);
	return (0);
}

/*
is_space

Propósito:
    Verifica si un carácter es un espacio o carácter de espacio en blanco.

Lógica:
    1. Retorna 1 si el carácter es un espacio, tabulación, salto de línea,
       retorno de carro, alimentación de formulario o tabulación vertical.
    2. Retorna 0 en caso contrario.

Comentarios:
    Es útil para ignorar espacios en el análisis de entradas.
*/

int	is_space(int c)
{
	if (c && (\
	c == ' ' || \
	c == '\t' || \
	c == '\n' || \
	c == '\r' || \
	c == '\f' || \
	c == '\v'))
		return (1);
	return (0);
}

/*
Resumen del archivo

Propósito:
    Proporciona funciones booleanas para validar caracteres en distintos
    contextos.

Lógica:
    1. valid_char: Verifica caracteres válidos para identificadores.
    2. no_word: Identifica operadores especiales.
    3. is_redir: Determina si un tipo corresponde a una redirección.
    4. is_space: Detecta espacios y caracteres en blanco.

Comentarios:
    Estas funciones booleanas son esenciales para el análisis sintáctico.
*/
