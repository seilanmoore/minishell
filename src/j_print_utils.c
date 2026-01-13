/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j_print_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:54:56 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 11:13:58 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
print_msg

Propósito:
    Imprime un mensaje en la salida de error y actualiza el estado.

Lógica:
    1. Usa `ft_putendl_fd` para imprimir el mensaje en el descriptor 2 (stderr).
    2. Actualiza `data->status` con el estado proporcionado.

Comentarios:
    Se utiliza para mostrar mensajes de error y actualizar el estado del shell.
*/

void	print_msg(t_data *data, char *msg, int status)
{
	ft_putendl_fd(msg, 2);
	data->status = status;
}

/*
print_array

Propósito:
    Imprime los elementos de un array de cadenas separados por espacios.

Lógica:
    1. Itera sobre el array, imprimiendo cada elemento.
    2. Si no es el último elemento, imprime un espacio entre ellos.

Comentarios:
    Facilita la visualización de arrays como argumentos o variables.
*/

void	print_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = -1;
	while (array[++i])
	{
		ft_putstr_fd(array[i], 2);
		if (array[i + 1])
			ft_putstr_fd(" ", 2);
	}
}

/* void	print_types(t_data *data)
{
	t_token	*head;
	t_token	*aux;

	head = data->input.tokens;
	while (head)
	{
		printf("TOKEN: \"%s\"	TYPE: %s(%d)	END_SPACE: %d\n", \
		head->token, type_to_char(head->type), head->type, head->end_space);
		aux = head->opt;
		if (aux)
			printf("\t--> OPTIONS:");
		while (aux && aux->type == OPTION)
		{
			printf(" %s", aux->token);
			aux = aux->next;
		}
		printf("\n");
		aux = head->arg;
		if (aux)
			printf("\t--> ARGS:");
		while (aux && aux->type == ARG)
		{
			printf(" %s", aux->token);
			aux = aux->next;
		}
		printf("\n");
		head = head->next;
	}
} */

/*
print_cmd_array

Propósito:
    Imprime los comandos y sus argumentos desde la lista de comandos.

Lógica:
    1. Itera sobre la lista de comandos en `data->input.command`.
    2. Imprime el nombre del comando (`cmd`) y sus argumentos
	usando `print_array`.
    3. Separa cada comando con una nueva línea.

Comentarios:
    Útil para depurar o verificar los comandos y argumentos procesados.
*/

void	print_cmd_array(t_data *data)
{
	t_cmd	*head;

	head = data->input.command;
	while (head)
	{
		printf("CMD_PATH: \"%s\" ARGUMENTS: ", head->cmd);
		print_array(head->args);
		printf("\n");
		head = head->next;
	}
}

/*
print_locals

Propósito:
    Imprime todas las variables locales definidas en el shell.

Lógica:
    1. Recorre la lista de variables locales en `data->locals`.
    2. Imprime cada variable en formato `clave=valor`.
    3. Restaura el puntero de la lista al nodo inicial.

Comentarios:
    Proporciona una vista de las variables locales actuales para depuración.
*/

void	print_locals(t_data *data)
{
	t_env	*head;

	head = data->locals;
	while (data->locals)
	{
		printf("%s=%s\n", data->locals->variable, data->locals->value);
		data->locals = data->locals->next;
	}
	data->locals = head;
}

/*
Resumen del archivo

Propósito:
    Proporciona utilidades para imprimir mensajes, arrays, comandos y variables.

Lógica:
    1. print_msg: Imprime mensajes de error y actualiza el estado.
    2. print_array: Imprime arrays de cadenas separadas por espacios.
    3. print_cmd_array: Muestra los comandos y argumentos en una lista.
    4. print_locals: Imprime las variables locales definidas.

Comentarios:
    Estas funciones son útiles para depuración y visualización
	de datos en el shell.
*/
