/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:49:42 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 11:52:44 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
check_new_var

Propósito:
    Añade o actualiza una variable en la lista de entorno.

Lógica:
    1. Si la variable ya existe (`new_var` no es nulo):
        - Libera su valor actual y asigna el nuevo valor.
    2. Si no existe:
        - Crea una nueva variable con el nombre y valor proporcionados.
        - La añade al final de la lista de entorno.

Comentarios:
    Gestiona la lógica para añadir o actualizar variables de entorno.
*/

void	check_new_var(t_env **lst, t_env *new_var, char *var, char *value)
{
	if (new_var)
	{
		free(new_var->value);
		if (value)
			new_var->value = ft_strdup(value);
		else
			new_var->value = ft_strdup("");
	}
	else
	{
		if (value)
			new_var = new_variable(var, value);
		else
			new_var = new_variable(var, "");
		if (last_variable(*lst))
			last_variable(*lst)->next = new_var;
		else
			*lst = new_var;
	}
}

/*
seek_and_replace

Propósito:
    Busca y actualiza una variable de entorno o la crea si no existe.

Lógica:
    1. Divide el argumento en `variable` y `value` usando `=` como delimitador.
    2. Valida la `variable` con `id_error`.
    3. Si es válida:
        - Busca la variable en la lista de entorno.
        - Llama a `check_new_var` para actualizarla o crearla.
    4. Retorna 1 si se realiza correctamente, 0 en caso de error.

Comentarios:
    Maneja la lógica de actualización o creación de variables de entorno.
*/

static int	seek_and_replace(t_data *data, char *arg)
{
	t_env	*new_var;
	char	*variable;
	char	*equal;

	variable = NULL;
	equal = ft_strchr(arg, '=');
	if (equal)
		variable = ft_substr(arg, 0, equal - arg);
	if (id_error(data, arg, variable, 1))
	{
		free(variable);
		return (0);
	}
	if (variable)
	{
		new_var = get_env_var(data->env, variable);
		check_new_var(\
				&(data->env), new_var, variable, equal + 1);
		free(variable);
	}
	return (1);
}

/*
export_builtin

Propósito:
    Implementa el comando interno `export` para gestionar variables de entorno.

Lógica:
    1. Itera sobre los argumentos recibidos.
    2. Llama a `seek_and_replace` para cada argumento.
        - Actualiza las variables de entorno si es necesario.
    3. Llama a `upd_env` para sincronizar la lista de entorno con el array.
    4. Retorna 0 si todos los argumentos son válidos, 1 si hay errores.

Comentarios:
    Gestiona la lógica principal del comando `export`.
*/

int	export_builtin(t_data *data, t_cmd *cmd)
{
	char	**args;
	int		update;
	int		fail;
	int		i;

	fail = 0;
	update = 0;
	args = cmd->args;
	i = 0;
	while (args[++i])
	{
		if (seek_and_replace(data, args[i]))
			update = 1;
		else
			fail = 1;
	}
	if (update)
		upd_env(data);
	if (fail)
		return (1);
	return (0);
}

/*
Resumen del archivo

Propósito:
    Implementa el comando interno `export` para añadir o actualizar variables
    de entorno.

Lógica:
    1. check_new_var: Añade o actualiza variables en la lista de entorno.
    2. seek_and_replace: Valida, actualiza o crea variables en la lista.
    3. export_builtin: Coordina la lógica para manejar múltiples argumentos.

Comentarios:
    Este archivo permite gestionar dinámicamente el entorno del shell
    mediante el comando `export`.
*/
