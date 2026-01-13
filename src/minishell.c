/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:28:08 by smoore-a          #+#    #+#             */
/*   Updated: 2025/01/20 22:37:31 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
handle_eof

Propósito: Verifica si la entrada es nula (EOF) y finaliza el shell.

Lógica:
    Si la línea de entrada (`data->input.raw_line`) es NULL:
        Llama a la función `exit_builtin` para liberar recursos
        y cerrar el shell.

Comentarios: Maneja el caso de EOF al presionar Ctrl+D.
*/

static void	handle_eof(t_data *data)
{
	if (!data->input.raw_line)
		exit_builtin(data, NULL);
}

/*
get_cwd

Propósito: Obtiene el directorio actual comprimido para mostrarlo en el prompt.

Lógica:
    Si `data->cwd` no está definido:
        Intenta obtener el valor de la variable de entorno `PWD`.
    Comprime el directorio usando `cwd_compress`.
    Devuelve el directorio comprimido concatenado con el prompt inicial.

Comentarios: Facilita la personalización del prompt con el directorio actual.
*/

static char	*get_cwd(t_data *data, char *prompt)
{
	t_env	*pwd;
	char	*short_cwd;
	char	*tmp;

	if (!(data->cwd))
	{
		pwd = get_env_var(data->env, "PWD");
		if (pwd)
			data->cwd = ft_strdup(pwd->value);
	}
	short_cwd = cwd_compress(data);
	if (short_cwd)
	{
		tmp = ft_strjoin(prompt, short_cwd);
		free(short_cwd);
	}
	else
		tmp = ft_strjoin(prompt, data->cwd);
	return (tmp);
}

/*
prompter

Propósito: Genera el prompt del shell, incluyendo usuario y directorio actual.

Lógica:
    Obtiene el nombre del usuario del entorno (`getenv("USER")`).
    Construye el prompt con el formato [USER:cwd]$.
    Usa `get_cwd` para incluir el directorio actual comprimido.

Comentarios: Define cómo se muestra el prompt en la terminal.
*/

static char	*prompter(t_data *data)
{
	char	*prompt;
	char	*tmp;

	data->user = getenv("USER");
	tmp = ft_strjoin("[", data->user);
	prompt = ft_strjoin(tmp, ": ");
	free (tmp);
	data->cwd = getcwd(NULL, 0);
	tmp = get_cwd(data, prompt);
	free(prompt);
	data->prompt = ft_strjoin(tmp, "]$ ");
	free(tmp);
	return (data->prompt);
}

/*
minishell

Propósito: Función principal del shell que gestiona entrada, parseo y ejecución.

Lógica:
    Inicializa `g_signal` a 0.
    Lee una línea de entrada con `readline`.
    Verifica EOF usando `handle_eof`.
    Si la entrada no está vacía:
        Guarda en el historial con `add_history`.
        Tokeniza, parsea y ejecuta el comando.
        Actualiza el código de salida con `data->exit_code`.
    Libera los recursos asociados a `data`.

Comentarios: Es el núcleo de la lógica del shell.
*/

void	minishell(t_data *data)
{
	g_signal = 0;
	data->input.raw_line = readline(prompter(data));
	handle_eof(data);
	if (data->input.raw_line && ft_strlen(data->input.raw_line) > 0 \
	&& !g_signal)
	{
		data->history = ft_strtrim(data->input.raw_line, "\n");
		if (data->history && ft_strlen(data->history) > 0)
			add_history(data->history);
		save_history();
		parser(data);
		if (syntax_error(data))
			data->exit_code = 2;
		else
			data->exit_code = execute(data);
		free(data->prev_exit_code);
		data->prev_exit_code = ft_itoa(data->exit_code);
	}
	free_data(data);
}

/*
Resumen del archivo

Propósito: Define la lógica principal del shell, incluyendo el manejo de
EOF, la generación del prompt y la ejecución de comandos.

Lógica:
    handle_eof: Verifica EOF y finaliza el shell si es necesario.
    get_cwd: Obtiene y comprime el directorio actual para el prompt.
    prompter: Genera el prompt personalizado del shell.
    minishell: Función principal que maneja el ciclo de lectura, parseo
               y ejecución de comandos.

Comentarios: Este archivo es fundamental para la interacción con el usuario,
gestionando tanto la interfaz del shell como el flujo de comandos.
*/
