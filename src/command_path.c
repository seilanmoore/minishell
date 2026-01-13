/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:15:30 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 11:03:01 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
append_slash

Propósito:
    Asegura que cada ruta en `data->paths` termine con una barra (`/`).

Lógica:
    1. Itera sobre las rutas en `data->paths`.
    2. Si una ruta no termina con `/`, la concatena usando `ft_strjoin`.
    3. Libera la memoria de la ruta anterior y actualiza el array.

Comentarios:
    Facilita la construcción de rutas completas para los comandos.
*/

static void	append_slash(t_data *data)
{
	char	*tmp;
	int		i;

	i = -1;
	while (data->paths[++i])
	{
		if (data->paths[i][ft_strlen(data->paths[i]) - 1] != '/')
		{
			tmp = data->paths[i];
			data->paths[i] = ft_strjoin(tmp, "/");
			free(tmp);
		}
	}
}

/*
get_env_paths

Propósito:
    Obtiene las rutas definidas en la variable de entorno `PATH` y las divide.

Lógica:
    1. Busca en la lista de variables de entorno el nodo `PATH`.
    2. Si se encuentra, divide su valor en rutas utilizando `ft_split`.
    3. Llama a `append_slash` para asegurar que las rutas terminen en `/`.

Comentarios:
    Prepara `data->paths` con todas las posibles rutas de comandos.
*/

static void	get_env_paths(t_data *data)
{
	t_env	*tmp;
	char	*line;

	line = NULL;
	tmp = data->env;
	while (tmp && ft_strcmp("PATH", tmp->variable))
		tmp = tmp->next;
	if (tmp)
	{
		line = tmp->value;
		if (line[0])
			data->paths = ft_split(line, ':');
		append_slash(data);
	}
}

/*
check_paths

Propósito:
    Comprueba si un comando tiene una ruta válida y actualiza su ubicación.

Lógica:
    1. Si el comando no es interno (`builtin`) y no tiene una barra (`/`):
        - Itera sobre `data->paths` y combina cada ruta con el comando.
        - Verifica acceso y ejecución con `access`.
        - Si es válido, actualiza `cmd` con la ruta completa y libera memoria.

Comentarios:
    Resuelve la ubicación de comandos externos que no tienen una ruta absoluta.
*/

static void	check_paths(t_data *data, t_cmd **head)
{
	char	*path;
	int		i;

	if (!(data->paths))
		get_env_paths(data);
	if (!(*head)->builtin && !ft_strchr((*head)->cmd, '/'))
	{
		i = -1;
		while (data->paths && data->paths[++i] \
		&& !ft_strchr((*head)->cmd, '/'))
		{
			path = ft_strjoin(data->paths[i], (*head)->cmd);
			if (access(path, F_OK | X_OK) == -1)
				free(path);
			else
			{
				free((*head)->cmd);
				(*head)->cmd = path;
			}
		}
	}
}

/*
assign_paths

Propósito:
    Asigna rutas válidas a todos los comandos de la lista.

Lógica:
    1. Recorre la lista de comandos en `data->input.command`.
    2. Llama a `check_paths` para validar y asignar rutas a cada comando.
    3. Avanza al siguiente comando en la lista.

Comentarios:
    Garantiza que todos los comandos tengan rutas válidas antes de ejecutarse.
*/

void	assign_paths(t_data *data)
{
	t_cmd	*head;

	head = data->input.command;
	while (head)
	{
		check_paths(data, &head);
		head = head->next;
	}
}

/*
Resumen del archivo

Propósito:
    Gestiona la resolución de rutas de comandos en el shell.

Lógica:
    1. append_slash: Asegura que las rutas en `data->paths` terminen con `/`.
    2. get_env_paths: Extrae y divide las rutas de la variable `PATH`.
    3. check_paths: Resuelve y asigna rutas completas a comandos externos.
    4. assign_paths: Valida y asigna rutas a todos los comandos en la lista.

Comentarios:
    Este archivo garantiza que los comandos tengan rutas válidas para su
    correcta ejecución en el shell.
*/
