/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:51:43 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 11:55:36 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
unset_builtin

Propósito:
    Implementa el comando interno `unset` para eliminar variables del entorno.

Lógica:
    1. Itera sobre los argumentos proporcionados.
    2. Para cada argumento:
        - Si existe en `env`, lo elimina usando `del_env`.
        - Si existe en `locals`, lo elimina de la lista local.
    3. Si se realizaron cambios en `env`, llama a `upd_env` para sincronizar.
    4. Retorna 0 al finalizar.

Comentarios:
    Este comando permite eliminar variables tanto del entorno global como local.
*/

int	unset_builtin(t_data *data, t_cmd *cmd)
{
	char	**arg;
	int		update;
	int		i;

	arg = cmd->args;
	update = 0;
	i = 0;
	while (arg[++i])
	{
		if (get_env_var(data->env, arg[i]))
		{
			del_env(&(data->env), arg[i]);
			update = 1;
		}
		if (get_env_var(data->locals, arg[i]))
			del_env(&(data->locals), arg[i]);
	}
	if (update)
		upd_env(data);
	return (0);
}

/*
Resumen del archivo

Propósito:
    Implementa la funcionalidad del comando interno `unset`.

Lógica:
    1. Itera sobre los argumentos.
    2. Elimina las variables correspondientes de `env` y `locals`.
    3. Actualiza el entorno si hubo cambios.

Comentarios:
    Este archivo proporciona la capacidad de gestionar dinámicamente
    la eliminación de variables del entorno y lista local.
*/
