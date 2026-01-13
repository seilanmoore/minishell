/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:15:47 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 10:19:28 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
get_dollar_value

Propósito: Obtiene el valor asociado a una variable que comienza con $.

Lógica:

	Si el nombre de la variable es nulo o vacío, retorna NULL.
	Si la variable es $, retorna el valor del proceso actual (data->process).
	Si la variable es ?, retorna el código de salida del último comando
	ejecutado (data->prev_exit_code).
	Busca en las variables de entorno global (data->env) usando get_env_var:
	  - Si la encuentra, devuelve su valor.
	Si no está en las variables globales, busca en las locales (data->locals):
	  - Si la encuentra, devuelve su valor.
	Si no se encuentra, retorna NULL.

Comentarios adicionales: Esta función es clave para expandir variables del
entorno y valores especiales como $?.
*/

char	*get_dollar_value(t_data *data, char *variable)
{
	t_env	*env_var;
	t_env	*local_head;

	if (!variable)
		return (NULL);
	if (*variable == '\0')
		return (NULL);
	if (!ft_strcmp(variable, "$"))
		return (data->process);
	if (!ft_strcmp(variable, "?"))
		return (data->prev_exit_code);
	env_var = get_env_var(data->env, variable);
	if (env_var)
		return (env_var->value);
	local_head = get_env_var(data->locals, variable);
	if (local_head)
		return (local_head->value);
	return (NULL);
}

/*
extract_id

Propósito: Extrae el identificador de una variable de entorno a partir
de un token que contiene $.

Lógica:

	Encuentra el primer $ en el token.
	Si el carácter siguiente es $ o ?, devuelve $$ o $? respectivamente
	como cadenas.
	Si no, recorre los caracteres válidos del identificador y calcula su
	longitud.
	Usa ft_substr para extraer el identificador como una subcadena desde el $.

Comentarios adicionales: Esta función determina qué parte del token se
considera un identificador válido para su posterior reemplazo.
*/

char	*extract_id(char *token)
{
	char	*identifier;
	int		len;

	identifier = ft_strchr(token, '$');
	if ((identifier + 1) && identifier[1] == '$')
		return (ft_strdup("$$"));
	if ((identifier + 1) && identifier[1] == '?')
		return (ft_strdup("$?"));
	len = 1;
	while (identifier[len] && valid_char(identifier[len]))
		len++;
	if (len == 1)
		return (ft_strdup("$"));
	return (ft_substr(identifier, 0, len));
}

/*
El archivo implementa funciones que:

  - Obtienen valores asociados a variables del entorno (get_dollar_value).
  - Extraen identificadores de variables del entorno a partir de
	cadenas (extract_id).

Ambas funciones se usan en la lógica de expansión para interpretar
correctamente expresiones como $USER, $$ y $?.
*/
