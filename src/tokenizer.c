/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:21:13 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 10:25:08 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
single_quote

Propósito: Procesa texto entre comillas simples (') y lo convierte en un token.

Lógica:

	Avanza al carácter siguiente después de la comilla inicial.
	Si encuentra una comilla de cierre inmediata o fin de línea, termina.
	Extrae todo el contenido hasta la próxima comilla simple.
	Marca el token resultante con el tipo S_QUOTE y un indicador de si termina
	con un espacio.

Comentarios: Las comillas simples no permiten expansión de variables; todo se
toma literalmente.
*/

static void	single_quote(t_data *data, t_var *var)
{
	var->aux1++;
	if (*(var->aux1) == '\0' || *(var->aux1) == '\'')
	{
		if (*(var->aux1) == '\'')
			var->aux1++;
		return ;
	}
	while (var->aux1[var->i] && var->aux1[var->i] != '\'')
		var->i++;
	var->aux = ft_substr(var->aux1, 0, var->i);
	if (var->aux1[var->i])
		var->i++;
	if (end_space(var))
		add_back_token(\
			&(data->input.tokens), new_token(var->aux, 0, S_QUOTE, 1));
	else
		add_back_token(\
			&(data->input.tokens), new_token(var->aux, 0, S_QUOTE, 0));
}

/*
double_quote

Propósito: Procesa texto entre comillas dobles (") y lo convierte en un token.

Lógica:

	Avanza al carácter siguiente después de la comilla inicial.
	Si encuentra otra comilla doble o fin de línea, termina.
	Extrae todo el contenido hasta la próxima comilla doble.
	Marca el token resultante con el tipo D_QUOTE y un indicador de si termina
	con un espacio.

Comentarios: Las comillas dobles permiten expansión de variables, por lo que este
token se tratará de forma diferente a uno con comillas simples.

*/

static void	double_quote(t_data *data, t_var *var)
{
	var->aux1++;
	if (var->aux1[var->i] == '\0')
		return ;
	if (var->aux1[var->i] == '\"')
	{
		var->aux1++;
		return ;
	}
	while (var->aux1[var->i] && var->aux1[var->i] != '\"')
		var->i++;
	var->aux = ft_substr(var->aux1, 0, var->i);
	if (var->aux1[var->i])
		var->i++;
	if (end_space(var))
		add_back_token(\
			&(data->input.tokens), new_token(var->aux, 0, D_QUOTE, 1));
	else
		add_back_token(\
			&(data->input.tokens), new_token(var->aux, 0, D_QUOTE, 0));
}

/*
handle_redir_char

Propósito: Procesa caracteres especiales relacionados con
redirecciones (<, >) y el pipe (|).

Lógica:

	Detecta:
		Redirecciones (<, <<, >, >>).
		Pipes (|).
	Extrae los caracteres especiales como un token individual.
	Marca el token como tipo NO_QUOTE.

Comentarios: Esto garantiza que operadores especiales sean tokens separados.
*/

void	handle_redir_char(t_data *data, t_var *var)
{
	if (var->aux1[var->i] == '<')
	{
		var->i++;
		if (var->aux1[var->i] && var->aux1[var->i] == '<')
			var->i++;
	}
	else if (var->aux1[var->i] == '>')
	{
		var->i++;
		if (var->aux1[var->i] && var->aux1[var->i] == '>')
			var->i++;
	}
	else if (var->aux1[var->i] == '|')
		var->i++;
	var->aux = ft_substr(var->aux1, 0, var->i);
	add_back_token(\
		&(data->input.tokens), new_token(var->aux, 0, NO_QUOTE, 1));
}

/*
characters

Propósito: Procesa caracteres genéricos que no están entre comillas ni son
operadores especiales.

Lógica:

	Recorre la línea hasta encontrar un espacio, una comilla, o un operador
	especial.
	Extrae este segmento como un token.
	Marca si el token termina con un espacio.

Comentarios: Es el comportamiento principal para dividir palabras o argumentos
de comandos.
*/

static void	characters(t_data *data, t_var *var)
{
	if (no_word(var->aux1[var->i]))
		return (handle_redir_char(data, var));
	while (var->aux1[var->i] && \
	!is_space(var->aux1[var->i]) && \
	var->aux1[var->i] != '\'' && \
	var->aux1[var->i] != '\"' && \
	var->aux1[var->i] != '|' && \
	var->aux1[var->i] != '<' && \
	var->aux1[var->i] != '>')
		var->i++;
	var->aux = ft_substr(var->aux1, 0, var->i);
	if (var->aux1[var->i] && \
	(var->aux1[var->i] == '|' || \
	var->aux1[var->i] == '<' || \
	var->aux1[var->i] == '>'))
		add_back_token(&(data->input.tokens), \
		new_token(var->aux, 0, NO_QUOTE, 1));
	else if (end_space(var))
		add_back_token(&(data->input.tokens), \
		new_token(var->aux, 0, NO_QUOTE, 1));
	else
		add_back_token(&(data->input.tokens), \
		new_token(var->aux, 0, NO_QUOTE, 0));
}

/*
tokenizer

Propósito: Se encarga de tokenizar toda la línea de entrada del shell.

Lógica:

	Inicializa un objeto t_var para manejar la posición actual en la línea.
	Itera sobre cada carácter de la línea:
		Ignora espacios.
		Procesa bloques delimitados por comillas simples o dobles.
		Maneja caracteres especiales (|, <, >).
		Procesa secuencias genéricas como palabras o números.
	Agrega cada token a la lista de tokens de entrada.

Comentarios: Es la función principal que transforma la línea de entrada en
una estructura de tokens manejables.
*/

void	tokenizer(t_data *data)
{
	t_var	var;

	var = (t_var){0};
	var.aux1 = data->input.raw_line;
	while (*var.aux1)
	{
		var.i = 0;
		var.aux = NULL;
		while (is_space(*var.aux1))
			var.aux1++;
		if (*var.aux1 && *var.aux1 == '\'')
			single_quote(data, &var);
		else if (*var.aux1 && *var.aux1 == '\"')
			double_quote(data, &var);
		else if (*var.aux1)
			characters(data, &var);
		var.aux1 = var.aux1 + var.i;
	}
}

/*
El archivo implementa las bases para tokenizar la línea de entrada en:

	Texto genérico (palabras, números).
	Tokens con comillas simples o dobles.
	Operadores especiales como redirecciones y pipes.

Esto organiza la entrada en elementos separados que el shell
interpretará y ejecutará.
*/
