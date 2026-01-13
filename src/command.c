/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:39:54 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 11:00:01 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
is_built

Propósito:
    Verifica si un comando dado es un comando interno del shell.

Lógica:
    1. Compara el nombre del comando con una lista de comandos internos
       como `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `history` y `exit`.
    2. Retorna 1 si el comando es interno, 0 en caso contrario.

Comentarios:
    Identifica comandos que serán ejecutados directamente por el shell.
*/

static int	is_built(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "history"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

/*
count_args

Propósito:
    Cuenta el número de argumentos asociados a un comando.

Lógica:
    1. Inicia con 1 para incluir el comando en sí.
    2. Recorre los tokens posteriores al comando hasta encontrar un `PIPE` o
       el final.
    3. Incrementa el contador por cada token de tipo `OPTION` o `ARG`.

Comentarios:
    Determina la cantidad de argumentos para reservar memoria al procesarlos.
*/

static int	count_args(t_token *token)
{
	t_token	*tmp;
	int		n_args;

	n_args = 1;
	tmp = token->next;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == OPTION || tmp->type == ARG)
			n_args++;
		tmp = tmp->next;
	}
	return (n_args);
}

/*
extract_args

Propósito:
    Extrae y construye una lista de argumentos a partir de los tokens.

Lógica:
    1. Reserva memoria para un array de cadenas basado en el resultado
       de `count_args`.
    2. Copia el contenido de los tokens de tipo `CMD`, `OPTION` y `ARG`.
    3. Termina el array con un puntero NULL.

Comentarios:
    Organiza los argumentos en una estructura fácil de manejar por el ejecutor.
*/

static char	**extract_args(t_token *token)//, int built)
{
	char	**args;
	int		i;

	args = ft_calloc(count_args(token) + 1, sizeof(char *));
	if (!args)
		return (NULL);
	args[0] = ft_strdup(token->token);
	token = token->next;
	i = 1;
	while (token && token->type != PIPE)
	{
		if (token->type == OPTION || token->type == ARG)
		{
			args[i] = ft_strdup(token->token);
			if (!args[i])
				return (args);
			i++;
		}
		token = token->next;
	}
	return (args);
}

/*
parse_cmd_opt

Propósito:
    Construye una lista de comandos a partir de los tokens analizados.

Lógica:
    1. Recorre los tokens y verifica si son de tipo `CMD`.
    2. Identifica si el comando es interno usando `is_built`.
    3. Extrae sus argumentos con `extract_args`.
    4. Crea un nodo de comando con `new_cmd` y lo añade a la lista de comandos.
    5. Asigna rutas a los comandos con `assign_paths`.

Comentarios:
    Conecta los comandos y sus argumentos en una estructura lista para ejecutar.
*/

void	parse_cmd_opt(t_data *data)
{
	t_cmd	*cmd;
	t_token	*tmp;
	char	**args;
	int		built;

	cmd = NULL;
	tmp = data->input.tokens;
	while (tmp)
	{
		if (tmp->token && tmp->type == CMD)
		{
			built = is_built(tmp->token);
			args = extract_args(tmp);
			cmd = new_cmd(tmp, args, built);
			if (cmd)
			{
				tmp->cmd = cmd;
				add_back_cmd(&(data->input.command), cmd);
			}
		}
		tmp = tmp->next;
	}
	assign_paths(data);
}

/*
Resumen del archivo

Propósito:
    Maneja la identificación y organización de comandos y sus argumentos.

Lógica:
    1. is_built: Verifica si un comando es interno.
    2. count_args: Cuenta los argumentos asociados a un comando.
    3. extract_args: Organiza los argumentos en un array de cadenas.
    4. parse_cmd_opt: Construye una lista de comandos con sus opciones y rutas.

Comentarios:
    Este archivo organiza los comandos y argumentos en una estructura
    lista para su ejecución.
*/
