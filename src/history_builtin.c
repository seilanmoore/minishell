/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:54:14 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 11:54:11 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
count_lines

Propósito:
    Cuenta la cantidad de líneas almacenadas en el archivo de historial.

Lógica:
    1. Abre el archivo de historial (`/tmp/.ms_history`) en modo lectura.
    2. Lee línea por línea usando `get_next_line`, incrementando un contador.
    3. Libera cada línea leída y cierra el archivo.
    4. Retorna el número total de líneas.

Comentarios:
    Permite determinar cuántas entradas están guardadas en el historial.
*/

static int	count_lines(void)
{
	char	*line;
	int		fd;
	int		i;

	fd = open("/tmp/.ms_history", O_RDONLY);
	if (fd == -1)
		return (handle_errno("/tmp/.ms_history"));
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		i++;
		free(line);
	}
	return (i);
}

/*
put_history

Propósito:
    Imprime el contenido del archivo de historial con numeración.

Lógica:
    1. Lee línea por línea desde el descriptor de archivo dado.
    2. Imprime el índice de la línea seguido de su contenido.
    3. Libera cada línea leída después de imprimirla.

Comentarios:
    Presenta el historial con un formato numerado en la salida estándar.
*/

static void	put_history(int fd)
{
	char	*line;
	int		i;

	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		ft_putnbr_fd(i++, STDOUT_FILENO);
		ft_putstr_fd(" ", STDOUT_FILENO);
		ft_putstr_fd(line, STDOUT_FILENO);
		free(line);
	}
}

/*
history_builtin

Propósito:
    Implementa el comando interno `history` para mostrar el historial.

Lógica:
    1. Calcula el número de líneas excedentes sobre 500 con `count_lines`.
    2. Abre el archivo de historial en modo lectura.
    3. Si hay más de 500 líneas, omite las excedentes.
    4. Llama a `put_history` para imprimir las últimas 500 líneas.
    5. Cierra el archivo y retorna 0.

Comentarios:
    Maneja la funcionalidad completa del comando `history`, limitando
    la salida a 500 entradas recientes.
*/

int	history_builtin(void)
{
	char	*line;
	int		fd;
	int		i;

	i = count_lines() - 500;
	fd = open("/tmp/.ms_history", O_RDONLY);
	if (fd == -1)
		return (handle_errno("/tmp/.ms_history"));
	if (i > 0)
	{
		while (i-- > 0)
		{
			line = get_next_line(fd);
			if (!line)
				break ;
			free(line);
		}
	}
	put_history(fd);
	close(fd);
	return (0);
}

/*
Resumen del archivo

Propósito:
    Implementa el comando interno `history` para mostrar entradas recientes
    del historial.

Lógica:
    1. count_lines: Cuenta las líneas en el archivo de historial.
    2. put_history: Imprime el historial con numeración.
    3. history_builtin: Muestra las últimas 500 entradas del historial.

Comentarios:
    Este archivo permite visualizar y gestionar el historial del shell.
*/
