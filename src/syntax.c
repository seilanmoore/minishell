/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 19:22:37 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 11:19:37 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
syntax_msg

Propósito:
    Imprime un mensaje de error de sintaxis relacionado con un token inesperado.

Lógica:
    1. Imprime "syntax error near unexpected token `" seguido del token.
    2. Agrega una comilla simple de cierre y un salto de línea.

Comentarios:
    Facilita la notificación de errores de sintaxis al usuario.
*/

void	syntax_msg(char *wildcard)
{
	ft_putstr_fd(MS, 2);
	ft_putstr_fd("syntax error near unexpected token `", 2);
	ft_putstr_fd(wildcard, 2);
	ft_putendl_fd("\'", 2);
}

/*
is_redirection

Propósito:
    Verifica si un tipo corresponde a una redirección.

Lógica:
    1. Retorna 1 si el tipo es `LEFT`, `LEFTT`, `RIGHT` o `RIGHTT`.
    2. Retorna 0 en caso contrario.

Comentarios:
    Permite identificar tokens relacionados con redirecciones.
*/

int	is_redirection(int type)
{
	if (type == LEFT || type == LEFTT || type == RIGHT || type == RIGHTT)
		return (1);
	return (0);
}

/*
is_word

Propósito:
    Determina si un tipo corresponde a una palabra válida en el
	contexto sintáctico.

Lógica:
    1. Retorna 0 si el tipo es nulo, `PIPE` o una redirección.
    2. Retorna 1 si el tipo representa una palabra válida.

Comentarios:
    Distingue palabras de operadores o tokens de control.
*/

int	is_word(int type)
{
	if (!type || type == PIPE || \
	type == LEFT || type == LEFTT || type == RIGHT || type == RIGHTT)
		return (0);
	return (1);
}

/*
syntax_error

Propósito:
    Verifica si hay errores de sintaxis en los tokens de entrada.

Lógica:
    1. Obtiene el primer token de la lista.
    2. Llama a `circle_1` para realizar verificaciones adicionales.
    3. Retorna 1 si se detecta un error, 0 en caso contrario.

Comentarios:
    Es la función principal para verificar errores de sintaxis en la entrada.
*/

int	syntax_error(t_data *data)
{
	t_token	*token;

	token = data->input.tokens;
	if (token && circle_1(token))
		return (1);
	return (0);
}

/*
Resumen del archivo

Propósito:
    Verifica y notifica errores de sintaxis en los tokens de entrada.

Lógica:
    1. syntax_msg: Imprime mensajes de error de sintaxis.
    2. is_redirection: Verifica si un tipo es una redirección.
    3. is_word: Determina si un tipo es una palabra válida.
    4. syntax_error: Detecta errores de sintaxis en los tokens.

Comentarios:
    Este archivo implementa las herramientas para analizar y reportar
    errores de sintaxis en el shell.
*/
