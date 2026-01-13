/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:52:14 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 11:54:58 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
pwd_builtin

Propósito:
    Implementa el comando interno `pwd` para mostrar el directorio actual.

Lógica:
    1. Obtiene la variable de entorno `PWD` usando `get_env_var`.
    2. Si la variable `PWD` existe y tiene un valor:
        - Imprime el valor en la salida estándar.
        - Retorna 0.
    3. Si no existe, retorna -1 para indicar error.

Comentarios:
    Este comando interno muestra el directorio actual utilizando la
    variable de entorno `PWD`.
*/

int	pwd_builtin(t_data *data)
{
	t_env	*pwd;

	pwd = get_env_var(data->env, "PWD");
	if (pwd && pwd->value)
		return (ft_putendl_fd(pwd->value, 1), 0);
	return (-1);
}

/*
Resumen del archivo

Propósito:
    Implementa el comando interno `pwd`.

Lógica:
    1. Recupera la variable de entorno `PWD`.
    2. Imprime el valor si está disponible, o retorna un error.

Comentarios:
    Este archivo proporciona la funcionalidad básica del comando `pwd`.
*/
