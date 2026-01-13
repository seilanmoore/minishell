/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:54:56 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 11:04:21 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
valid_ident

Propósito:
    Verifica si una cadena es un identificador válido.

Lógica:
    1. Si la cadena es nula o vacía, retorna 1 o 0 respectivamente.
    2. Si el primer carácter es un dígito, retorna 0.
    3. Itera sobre la cadena para verificar que solo contiene letras, 
       números, `$`, o `_`.

Comentarios:
    Garantiza que los identificadores sigan las reglas de sintaxis.
*/

int	valid_ident(char *str)
{
	if (!str)
		return (1);
	if (*str == '\0')
		return (0);
	if (ft_isdigit(*str))
		return (0);
	while (*str)
	{
		if (*str != '_' && *str != '$' && (*str < 'a' || *str > 'z') && \
			(*str < 'A' || *str > 'Z') && (*str < '0' || *str > '9'))
			return (0);
		str++;
	}
	return (1);
}

/*
split_token

Propósito:
    Divide un token en dos partes usando `=` como delimitador.

Lógica:
    1. Reserva memoria para un array de dos cadenas.
    2. Si el token comienza con `=`, guarda la cadena completa en el array.
    3. Busca el carácter `=` en el token:
        - Divide el token antes y después de `=` en dos cadenas.
    4. Retorna el array resultante.

Comentarios:
    Se utiliza para manejar asignaciones como `VAR=valor`.
*/

char	**split_token(char *token)
{
	char	**array;
	int		i;

	array = ft_calloc(3, sizeof(char *));
	i = -1;
	if (token[0] == '=')
	{
		array[0] = ft_strdup(token);
		return (array);
	}
	while (token[++i])
	{
		if (token[i] == '=')
		{
			array[0] = ft_substr(token, 0, i);
			array[1] = ft_strdup(&token[++i]);
			return (array);
		}
	}
	return (NULL);
}

/*
rev_split

Propósito:
    Combina un array de cadenas en una sola cadena, separada por espacios.

Lógica:
    1. Inicializa la cadena con el primer elemento del array.
    2. Itera sobre el resto del array, concatenando cada elemento con un espacio.
    3. Libera memoria intermedia y retorna la cadena combinada.

Comentarios:
    Inverso de un split; útil para reconstruir cadenas desde un array.
*/

char	*rev_split(char **array)
{
	char	*str;
	char	*prev_str;
	char	*aux;
	int		i;

	i = 0;
	str = ft_strdup(array[i]);
	while (array[++i])
	{
		prev_str = str;
		aux = ft_strjoin(str, " ");
		str = ft_strjoin(aux, array[i]);
		free(aux);
		free(prev_str);
		if (!str)
			break ;
	}
	return (str);
}

/*
get_envp_var

Propósito:
    Obtiene el valor de una variable de entorno desde un array `envp`.

Lógica:
    1. Itera sobre el array `envp` buscando un nombre de variable que coincida.
    2. Calcula la longitud del nombre hasta `=`.
    3. Si hay coincidencia exacta, retorna el valor asociado después de `=`.

Comentarios:
    Permite obtener valores de variables desde un entorno personalizado.
*/

char	*get_envp_var(char **envp, char *var)
{
	int	v_len;
	int	i;

	if (!envp)
		return (NULL);
	i = -1;
	while (envp[++i])
	{
		v_len = ft_strchr(envp[i], '=') - envp[i];
		if (!ft_strncmp(envp[i], var, v_len))
		{
			if (ft_strlen(var) == (size_t)v_len)
				return (ft_strchr(envp[i], '=') + 1);
		}
	}
	return (NULL);
}

/*
Resumen del archivo

Propósito:
    Proporciona funciones generales para validar, dividir y manipular cadenas.

Lógica:
    1. valid_ident: Verifica si una cadena es un identificador válido.
    2. split_token: Divide cadenas por `=` en clave y valor.
    3. rev_split: Reconstruye cadenas desde un array.
    4. get_envp_var: Obtiene valores de variables desde el entorno.

Comentarios:
    Estas utilidades son fundamentales para procesar cadenas en el shell.
*/
