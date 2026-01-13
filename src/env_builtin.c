/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:50:43 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 11:50:44 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
env_builtin

Propósito:
    Implementa el comando interno `env` para imprimir las variables de entorno.

Lógica:
    1. Verifica si el array de entorno (`envp`) está inicializado.
    2. Si está vacío, retorna 0 sin imprimir nada.
    3. Itera sobre `envp`, imprimiendo cada variable en la salida estándar.

Comentarios:
    Proporciona una forma sencilla de listar las variables de entorno actuales.
*/

int	env_builtin(t_data *data)
{
	int	i;

	if (!data->envp)
		return (0);
	i = -1;
	while (data->envp[++i])
		ft_putendl_fd(data->envp[i], 1);
	return (0);
}

/*
Resumen del archivo

Propósito:
    Implementa el comando interno `env`.

Lógica:
    1. Verifica la existencia de variables en `envp`.
    2. Imprime cada variable con un salto de línea.

Comentarios:
    Este archivo implementa el comportamiento estándar
	del comando `env` en el shell.
*/
