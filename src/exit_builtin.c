/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:50:58 by smoore-a          #+#    #+#             */
/*   Updated: 2025/01/22 13:00:22 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
contain_digit

Propósito:
    Verifica si una cadena contiene caracteres numéricos.

Lógica:
    1. Itera sobre cada carácter de la cadena.
    2. Retorna 1 si encuentra un carácter numérico.
    3. Si no contiene dígitos, retorna 0.

Comentarios:
    Es utilizado para validar argumentos numéricos en el comando `exit`.
*/

static int	contain_digit(char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (ft_isdigit(*str))
			return (1);
		str++;
	}
	return (0);
}

/*
several_args

Propósito:
    Maneja múltiples argumentos pasados al comando `exit`.

Lógica:
    1. Cuenta los argumentos en el array.
    2. Si hay más de dos, establece un código de error (1) y muestra un mensaje.
    3. Si hay exactamente uno,
	convierte el argumento numérico al código de salida.

Comentarios:
    Maneja el caso en el que `exit` recibe demasiados argumentos.
*/

static void	several_args(char **args, int *exit_)
{
	int	i;

	i = 0;
	while (args[++i])
		;
	if (i > 2)
	{
		*exit_ = 1;
		ft_putendl_fd(MS "exit: too many arguments", 2);
	}
	else if (args[1])
		*exit_ = ft_atoi(args[1]);
}

/*
not_valid_arg

Propósito:
    Verifica si el argumento del comando `exit` es válido.

Lógica:
    1. Si hay un argumento, verifica si contiene solo dígitos.
    2. Si no es válido, imprime un mensaje de error y
	establece el código de salida en 2.
    3. Retorna 0 si el argumento no es válido, 1 si lo es.

Comentarios:
    Garantiza que los argumentos de `exit` sean numéricos o muestra un error.
*/

static int	not_valid_arg(char **args, int *exit_)
{
	if (args[1])
	{
		if (contain_digit(args[1]))
			*exit_ = ft_atoi(args[1]);
		else
		{
			*exit_ = 2;
			ft_putstr_fd(MS "exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			return (0);
		}
	}
	return (1);
}

/*
exit_builtin

Propósito:
    Implementa el comando interno `exit`.

Lógica:
    1. Imprime "exit" en la salida estándar.
    2. Valida los argumentos con `not_valid_arg` y `several_args`.
    3. Libera todos los recursos (memoria, historial, entorno).
    4. Termina el programa con `exit`, usando el código de salida especificado.

Comentarios:
    Maneja la funcionalidad completa del comando `exit`, incluyendo validaciones.
*/

int	exit_builtin(t_data *data, t_cmd *cmd)
{
	char	**args;
	int		exit_;

	exit_ = -1;
	args = NULL;
	ft_putendl_fd("exit", 1);
	if (cmd)
	{
		args = cmd->args;
		if (not_valid_arg(args, &exit_))
			several_args(args, &exit_);
	}
	data->input.tokens = data->first_token;
	ft_free((void *)&(data->pids));
	ft_free((void *)&(data->process));
	ft_free((void *)&(data->prev_exit_code));
	free_local(data);
	free_environment(data);
	free_data(data);
	rl_clear_history();
	clear_history();
	if (exit_ != -1)
		exit(exit_);
	exit(EXIT_SUCCESS);
}

/*
Resumen del archivo

Propósito:
    Implementa el comando interno `exit` con validaciones y
	liberación de recursos.

Lógica:
    1. contain_digit: Valida si los argumentos son numéricos.
    2. several_args: Maneja errores al recibir demasiados argumentos.
    3. not_valid_arg: Verifica y maneja argumentos no válidos.
    4. exit_builtin: Valida argumentos, libera recursos y termina el shell.

Comentarios:
    Este archivo proporciona una implementación robusta del comando `exit`.
*/
