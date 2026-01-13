/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checks2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:14:41 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 10:55:59 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
check_option_arg

Propósito:
    Verifica si un token es una opción (`-`) o un argumento de un comando.

Lógica:
    1. Si el token no está entre comillas, comienza con `-`, y el comando está
       activo pero no se han definido argumentos:
        - Asigna el tipo `OPTION` al token.
    2. Si el comando está activo:
        - Activa el modo de argumento (`in_arg`) y asigna el tipo `ARG`.
    3. Retorna 1 si el tipo se asignó, 0 en caso contrario.

Comentarios:
    Diferencia entre opciones y argumentos dentro del contexto de un comando.
*/

static int	check_option_arg(t_data *data, t_token *ptr, int i)
{
	if (ptr->quote == NO_QUOTE && \
		ptr->token[0] == '-' && \
		data->in_cmd && data->in_arg == 0)
		return (access_to_types(data, i, OPTION), 1);
	if (data->in_cmd)
	{
		data->in_arg = 1;
		return (access_to_types(data, i, ARG), 1);
	}
	return (0);
}

/*
check_cmds

Propósito:
    Determina si un token es un comando y actualiza su tipo y estado.

Lógica:
    1. Llama a `check_option_arg` para procesar opciones o argumentos.
    2. Si no es una opción o argumento:
        - Incrementa el contador de comandos (`n_cmd`).
        - Activa el estado de comando (`in_cmd`) y desactiva
		argumentos (`in_arg`).
        - Asigna el tipo `CMD` al token.

Comentarios:
    Es la función principal para identificar comandos en la lista de tokens.
*/

int	check_cmds(t_data *data, t_token *ptr, int i)
{
	if (check_option_arg(data, ptr, i))
		return (1);
	data->n_cmd++;
	data->in_cmd = 1;
	data->in_arg = 0;
	access_to_types(data, i, CMD);
	return (1);
}

/*
Resumen del archivo

Propósito:
    Verifica y asigna tipos a tokens relacionados con comandos, opciones
    y argumentos.

Lógica:
    1. check_option_arg: Clasifica tokens como opciones o argumentos.
    2. check_cmds: Identifica comandos y actualiza su tipo y estado.

Comentarios:
    Este archivo proporciona funciones esenciales para diferenciar entre
    comandos, opciones y argumentos en el proceso de análisis.
*/
