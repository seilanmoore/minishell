/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:48:46 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 11:49:02 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
update_var

Propósito:
    Actualiza las variables de entorno `PWD` y `OLDPWD`
	tras un cambio de directorio.

Lógica:
    1. Obtiene `OLDPWD` desde la lista de entorno y actualiza su valor con `cwd`.
    2. Obtiene `PWD` y lo actualiza con la nueva ruta usando `getcwd`.
    3. Llama a `upd_env` para sincronizar los cambios con el entorno.

Comentarios:
    Mantiene actualizadas las variables relacionadas con la ubicación actual.
*/

static void	update_var(t_data *data)
{
	t_env	*variable;

	variable = get_env_var(data->env, "OLDPWD");
	if (variable)
	{
		free(variable->value);
		variable->value = ft_strdup(data->cwd);
		upd_env(data);
	}
	variable = get_env_var(data->env, "PWD");
	if (variable)
	{
		free(variable->value);
		variable->value = getcwd(NULL, 0);
		upd_env(data);
	}
}

/*
cd_home

Propósito:
    Cambia el directorio actual al directorio `HOME`.

Lógica:
    1. Si `HOME` está definido, intenta cambiar al directorio indicado.
    2. Si el cambio falla, intenta volver a `cwd` o, como último recurso, a `/`.
    3. Si `HOME` no está definido, imprime un mensaje de error.

Comentarios:
    Gestiona los casos donde `cd` se invoca sin argumentos.
*/

static int	cd_home(t_data *data, char *home)
{
	if (home)
	{
		if (chdir(home) == -1)
		{
			if (chdir(data->cwd) == -1)
			{
				if (chdir("/") == -1)
					return (1);
			}
			return (0);
		}
		return (0);
	}
	else
	{
		ft_putendl_fd(MS CD CD_HOME, 2);
		return (1);
	}
}

/*
handle_cwd_fail

Propósito:
    Maneja fallos al recuperar el directorio actual tras un cambio de directorio.

Lógica:
    1. Intenta cambiar a `cwd` y verificar con `getcwd`.
    2. Si falla, cambia al directorio raíz `/`.

Comentarios:
    Asegura un manejo adecuado en caso de errores al obtener el directorio.
*/

static int	handle_cwd_fail(t_data *data)
{
	char	*cwd;

	chdir(data->cwd);
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		free(cwd);
		return (1);
	}
	chdir("/");
	return (0);
}

/*
cd_path

Propósito:
    Cambia el directorio actual al especificado en `path`.

Lógica:
    1. Si `path` no está definido, llama a `cd_home`.
    2. Intenta cambiar al directorio especificado.
    3. Si falla, imprime un mensaje de error y retorna 1.
    4. Verifica `cwd` tras el cambio y maneja fallos con `handle_cwd_fail`.

Comentarios:
    Gestiona los cambios de directorio especificados en los argumentos.
*/

static int	cd_path(t_data *data, char *path, char *home)
{
	char	*cwd;

	if (!path)
		return (cd_home(data, home));
	if (chdir(path) == -1)
	{
		ft_putstr_fd(MS CD, 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		if (handle_cwd_fail(data) == 1)
			return (1);
	}
	free(cwd);
	return (0);
}

/*
cd_builtin

Propósito:
    Implementa el comando interno `cd` para cambiar de directorio.

Lógica:
    1. Valida los argumentos para detectar
	opciones no soportadas o demasiados argumentos.
    2. Llama a `cd_path` con la ruta proporcionada o `HOME` como predeterminado.
    3. Actualiza las variables `PWD` y `OLDPWD` tras el cambio.

Comentarios:
    Proporciona la funcionalidad del comando `cd` en el shell.
*/

int	cd_builtin(t_data *data, t_cmd *cmd)
{
	t_env	*home;
	int		exit_;

	exit_ = 0;
	if (cmd->args[1] && cmd->args[1][0] == '-')
		return (print_msg(data, MS CD CD_OPT, -1), 1);
	if (cmd->args[1] && cmd->args[2])
		return (print_msg(data, MS CD CD_ARG, -1), 1);
	home = get_env_var(data->env, "HOME");
	if (home)
		exit_ = cd_path(data, cmd->args[1], home->value);
	else
		exit_ = cd_path(data, cmd->args[1], NULL);
	update_var(data);
	return (exit_);
}

/*
Resumen del archivo

Propósito:
    Implementa la funcionalidad del comando interno `cd`.

Lógica:
    1. update_var: Actualiza `PWD` y `OLDPWD` tras un cambio de directorio.
    2. cd_home: Cambia al directorio `HOME` si está definido.
    3. handle_cwd_fail: Maneja errores al obtener el directorio actual.
    4. cd_path: Cambia al directorio especificado o maneja errores.
    5. cd_builtin: Ejecuta el comando `cd`,
	validando argumentos y actualizando variables.

Comentarios:
    Este archivo implementa el comando `cd`,
	gestionando errores y actualizaciones del entorno.
*/
