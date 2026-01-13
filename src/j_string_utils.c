/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j_string_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:54:56 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 11:15:10 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
ft_strcmp

Propósito:
    Compara dos cadenas para verificar si son iguales.

Lógica:
    1. Retorna 1 si alguna cadena es nula o tienen diferentes longitudes.
    2. Compara carácter por carácter y retorna 1 si son distintos.
    3. Retorna 0 si ambas cadenas son idénticas.

Comentarios:
    Es una implementación personalizada de comparación de cadenas.
*/

int	ft_strcmp(const char *str1, const char *str2)
{
	int	i;

	if (!str1 || !str2)
		return (1);
	if (ft_strlen(str1) != ft_strlen(str2))
		return (1);
	i = -1;
	while (str1[++i])
	{
		if (str1[i] != str2[i])
			return (1);
	}
	return (0);
}

/*
cwd_compress

Propósito:
    Comprime el directorio actual reemplazando el prefijo del HOME por `~`.

Lógica:
    1. Obtiene el valor de `HOME` desde `envp` o `getenv`.
    2. Si `cwd` comienza con `HOME`, reemplaza el prefijo con `~` usando
       `str_replace`.
    3. Retorna la versión comprimida del directorio.

Comentarios:
    Facilita la representación simplificada del directorio actual en el prompt.
*/

char	*cwd_compress(t_data *data)
{
	char	*short_cwd;
	char	*home;

	short_cwd = NULL;
	if (!data->envp)
		home = getenv("HOME");
	else
		home = get_envp_var(data->envp, "HOME");
	if (!ft_strncmp(data->cwd, home, ft_strlen(home)))
		short_cwd = str_replace(data->cwd, home, "~");
	return (short_cwd);
}

/*
type_to_char

Propósito:
    Convierte un tipo de token a su representación textual.

Lógica:
    1. Verifica el tipo de token (`CMD`, `OPTION`, `PIPE`, etc.).
    2. Retorna la cadena correspondiente al tipo.
    3. Si el tipo no coincide, retorna "NO_TYPE".

Comentarios:
    Se utiliza para depuración y representación textual de tipos de tokens.
*/

char	*type_to_char(int type)
{
	if (type == CMD)
		return ("CMD");
	if (type == OPTION)
		return ("OPTION");
	if (type == ARG)
		return ("ARGUMENT");
	if (type == PIPE)
		return ("PIPE");
	if (type == LEFT)
		return ("<");
	if (type == RIGHT)
		return (">");
	if (type == LEFTT)
		return ("<<");
	if (type == RIGHTT)
		return (">>");
	if (type == FILE)
		return ("FILE");
	if (type == HERE)
		return ("HEREDOC");
	if (type == LOCAL)
		return ("LOCAL");
	if (type == LOCAL_VAL)
		return ("VALUE");
	return ("NO_TYPE");
}

/*
str_replace

Propósito:
    Reemplaza la primera ocurrencia de una subcadena en una cadena principal.

Lógica:
    1. Busca la posición de `needle` en `haystack`.
    2. Divide `haystack` antes y después de `needle`.
    3. Une las partes con `replace` en lugar de `needle`.
    4. Retorna la nueva cadena resultante.

Comentarios:
    Es útil para modificaciones específicas en cadenas, como rutas o variables.
*/

char	*str_replace(char *haystack, char *needle, char *replace)
{
	char	*str;
	char	*ptr;
	char	*aux;
	int		len;

	if (!haystack || !needle)
		return (ft_strdup(haystack));
	ptr = ft_strnstr(haystack, needle, ft_strlen(haystack));
	len = ptr - haystack;
	str = ft_substr(haystack, 0, len);
	if (!str)
		return (NULL);
	ptr = ptr + ft_strlen(needle);
	aux = str;
	str = ft_strjoin(str, replace);
	if (!str)
		return (NULL);
	free (aux);
	aux = str;
	str = ft_strjoin(str, ptr);
	free(aux);
	if (!str)
		return (NULL);
	return (str);
}

/*
Resumen del archivo

Propósito:
    Proporciona utilidades para manipulación y conversión de cadenas.

Lógica:
    1. ft_strcmp: Compara dos cadenas para verificar igualdad.
    2. cwd_compress: Simplifica rutas reemplazando el prefijo HOME con `~`.
    3. type_to_char: Convierte tipos de tokens en representaciones textuales.
    4. str_replace: Reemplaza subcadenas en una cadena principal.

Comentarios:
    Estas funciones son esenciales para la manipulación avanzada de cadenas
    en el shell.
*/
