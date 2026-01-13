/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:47:35 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 11:49:59 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
check_option

Propósito:
    Verifica si la opción `-n` está presente en los argumentos.

Lógica:
    1. Compara el primer argumento con `-n` utilizando `ft_strcmp`.
    2. Si coincide, retorna 0 (indicando que la opción está presente).
    3. Si no coincide, imprime los argumentos restantes.

Comentarios:
    Maneja la funcionalidad de suprimir el salto de línea en `echo`.
*/

static int	check_option(char **args)
{
	int	i;

	if (ft_strcmp(args[1], "-n"))
		return (0);
	i = 1;
	while (args[++i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
	}
	return (1);
}

/*
echo_builtin

Propósito:
    Implementa el comando interno `echo`.

Lógica:
    1. Obtiene los argumentos del comando.
    2. Llama a `check_option` para verificar la presencia de `-n`.
    3. Itera sobre los argumentos restantes, imprimiéndolos con espacios.
    4. Si `-n` no está presente, agrega un salto de línea al final.

Comentarios:
    Reproduce el comportamiento estándar del comando `echo`.
*/

int	echo_builtin(t_cmd *cmd)
{
	char	**args;
	int		i;

	args = cmd->args;
	if (check_option(args))
		return (0);
	i = 0;
	while (args[++i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
	}
	ft_putchar_fd('\n', 1);
	return (0);
}

/*
Resumen del archivo

Propósito:
    Implementa el comando interno `echo` con soporte para la opción `-n`.

Lógica:
    1. check_option: Verifica si `-n` está presente y ajusta la impresión.
    2. echo_builtin: Imprime los argumentos con o sin salto de línea
	según la opción.

Comentarios:
    Este archivo proporciona la funcionalidad del comando `echo`
	dentro del shell.
*/
