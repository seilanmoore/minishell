/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:17:10 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 10:44:15 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_signal;

/*
handle_quit

Propósito:
    Captura la señal SIGQUIT (`Ctrl+\`) y maneja la interrupción.

Lógica:
    1. Imprime "Quit (core dumped)" en la salida de error estándar.
    2. Actualiza la variable global `g_signal` a 131 para indicar la señal.

Comentarios:
    Maneja interrupciones específicas como las generadas por SIGQUIT.
*/

void	handle_quit(int sig)
{
	(void)sig;
	g_signal = 131;
	ft_putendl_fd("Quit (core dumped)", 2);
}

/*
handle_signal

Propósito:
    Captura la señal SIGINT (`Ctrl+C`) y maneja el flujo según el estado actual.

Lógica:
    1. Si hay procesos activos (`g_signal` != 0):
        - Escribe una nueva línea y envía SIGINT al proceso activo.
    2. Si no hay procesos:
        - Resetea la línea de entrada del shell (`readline`).

Comentarios:
    Garantiza que el shell reaccione correctamente a interrupciones de usuario.
*/

void	handle_signal(int sig)
{
	(void)sig;
	if (g_signal)
	{
		write(1, "\n", 1);
		kill(g_signal, SIGINT);
	}
	else
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_signal = 0;
}

/*
main

Propósito:
    Inicializa el shell, configura las señales y ejecuta el ciclo principal.

Lógica:
    1. Ignora SIGQUIT y establece `handle_signal` para SIGINT.
    2. Inicializa la estructura de datos principal (`init_data`).
    3. Carga el historial con `get_history`.
    4. Ejecuta un bucle infinito invocando la función `minishell`.

Comentarios:
    Es el punto de entrada principal que define la configuración y ciclo
	del shell.
*/

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signal);
	init_data(&data, envp);
	get_history();
	while (1)
		minishell(&data);
	exit(0);
}

/*
Resumen del archivo

Propósito:
    Configura el manejo de señales y lanza el ciclo principal del shell.

Lógica:
    1. handle_quit: Captura y maneja interrupciones por SIGQUIT.
    2. handle_signal: Maneja SIGINT para interrupciones interactivas.
    3. main: Configura el entorno y ejecuta el bucle principal del shell.

Comentarios:
    Este archivo establece la base del comportamiento interactivo del shell.
*/
