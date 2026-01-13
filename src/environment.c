/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:13:57 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 11:35:25 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
envp_to_array

Propósito:
    Convierte la lista de variables de entorno (`t_env`) en un array de cadenas.

Lógica:
    1. Reserva memoria para el array de cadenas basado en el tamaño de la lista.
    2. Itera sobre la lista `env`, concatenando cada variable y valor con `=`.
    3. Almacena cada resultado en `data->envp` y libera recursos temporales.

Comentarios:
    Permite manejar las variables de entorno
	en un formato compatible con `execve`.
*/

void	envp_to_array(t_data *data)
{
	t_env	*head;
	char	*tmp;
	int		i;

	if (!data->env)
		return ;
	head = data->env;
	i = 0;
	data->envp = ft_calloc(env_size(data->env) + 1, sizeof(char *));
	while (data->env)
	{
		tmp = ft_strjoin(data->env->variable, "=");
		data->envp[i++] = ft_strjoin(tmp, data->env->value);
		free(tmp);
		data->env = data->env->next;
	}
	data->env = head;
}

/*
envp_to_lst

Propósito:
    Convierte el array de variables de entorno (`envp`) en
	una lista de nodos `t_env`.

Lógica:
    1. Libera la lista de entorno actual si existe.
    2. Itera sobre `envp`, separando cada cadena
	en `variable` y `value` usando `=` como delimitador.
    3. Crea nodos `t_env` con `new_variable` y los agrega a la lista.

Comentarios:
    Sincroniza el array de entorno con una representación en lista enlazada.
*/

void	envp_to_lst(t_data *data)
{
	char			*variable;
	char			*value;
	int				len;
	int				i;

	free_env_lst(data);
	if (!data->envp)
		return ;
	i = -1;
	while (data->envp[++i])
	{
		len = ft_strchr(data->envp[i], '=') - data->envp[i];
		variable = ft_substr(data->envp[i], 0, len);
		value = ft_substr(
				data->envp[i], len + 1, ft_strlen(data->envp[i]));
		add_back_variable(&(data->env), new_variable(variable, value));
		free(variable);
		free(value);
	}
}

/*
Resumen del archivo

Propósito:
    Proporciona funciones para convertir entre el formato de array y lista
    de variables de entorno.

Lógica:
    1. envp_to_array: Convierte una lista de entorno en un array.
    2. envp_to_lst: Convierte un array de entorno en una lista enlazada.

Comentarios:
    Este archivo facilita la interoperabilidad entre representaciones de
    variables de entorno en el shell.
*/
