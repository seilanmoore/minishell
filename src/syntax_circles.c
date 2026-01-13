/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_circles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 21:44:49 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 11:20:28 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
circle_4

Propósito:
    Verifica la validez sintáctica de palabras y redirecciones en una secuencia.

Lógica:
    1. Si el token es una palabra, continúa con `circle_3`.
    2. Si el token es una redirección, llama a `circle_2`.
    3. Si no es válido, muestra un mensaje de error con `syntax_msg`.

Comentarios:
    Maneja errores en cadenas relacionadas con redirecciones o palabras.
*/

int	circle_4(t_token *token, t_token *prev)
{
	if (token)
	{
		if (is_word(token->type))
			return (circle_3(token->next, token));
		if (is_redirection(token->type))
			return (circle_2(token->next, token));
	}
	return (syntax_msg(prev->token), 1);
}

/*
circle_3

Propósito:
    Analiza secuencias de palabras, pipes y redirecciones en los tokens.

Lógica:
    1. Si el token es `PIPE`, llama a `circle_4` para procesar el siguiente.
    2. Si el token es una palabra, continúa con `circle_3`.
    3. Si es una redirección, llama a `circle_2`.
    4. Si no es válido, muestra un mensaje de error con `syntax_msg`.

Comentarios:
    Verifica la sintaxis de combinaciones complejas con pipes y redirecciones.
*/

int	circle_3(t_token *token, t_token *prev)
{
	if (!token)
		return (0);
	if (token->type == PIPE)
		return (circle_4(token->next, token));
	if (is_word(token->type))
		return (circle_3(token->next, token));
	if (is_redirection(token->type))
		return (circle_2(token->next, token));
	return (syntax_msg(prev->token), 1);
}

/*
circle_2

Propósito:
    Valida tokens tras una redirección y determina la validez de la secuencia.

Lógica:
    1. Si el token es una palabra, llama a `circle_3` para procesarlo.
    2. Si no hay un token válido, muestra un mensaje de error con `syntax_msg`.

Comentarios:
    Asegura que las redirecciones estén seguidas de palabras válidas.
*/

int	circle_2(t_token *token, t_token *prev)
{
	if (token)
	{
		if (is_word(token->type))
			return (circle_3(token->next, token));
	}
	return (syntax_msg(prev->token), 1);
}

/*
circle_1

Propósito:
    Inicia la validación de sintaxis en una lista de tokens.

Lógica:
    1. Si el token es una palabra, continúa con `circle_3`.
    2. Si el token es una redirección, llama a `circle_2`.
    3. Si no es válido, muestra un mensaje de error con `syntax_msg`.

Comentarios:
    Es el punto de entrada principal para validar la sintaxis de los tokens.
*/

int	circle_1(t_token *token)
{
	if (is_word(token->type))
		return (circle_3(token->next, token));
	if (is_redirection(token->type))
		return (circle_2(token->next, token));
	return (syntax_msg(token->token), 1);
}

/*
Resumen del archivo

Propósito:
    Implementa un análisis sintáctico estructurado basado en validaciones
    circulares para palabras, pipes y redirecciones.

Lógica:
    1. circle_1: Punto de entrada para iniciar la validación.
    2. circle_2: Valida tokens tras redirecciones.
    3. circle_3: Verifica secuencias de palabras y pipes.
    4. circle_4: Procesa errores relacionados con redirecciones o palabras.

Comentarios:
    Este archivo asegura que los tokens de entrada sigan una sintaxis válida
    antes de su ejecución en el shell.
*/
