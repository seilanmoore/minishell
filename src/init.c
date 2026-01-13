/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:02:34 by smoore-a          #+#    #+#             */
/*   Updated: 2024/12/04 10:42:06 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
upd_shlvl

Propósito: Incrementa el nivel de shell (`SHLVL`) en el entorno.

Lógica:
    Busca la variable `SHLVL` en el entorno.
    Convierte su valor a entero, lo incrementa, y lo actualiza en el entorno.

Comentarios: Se asegura de reflejar correctamente el nivel del shell en
cada inicio.
*/

static void	upd_shlvl(t_data *data)
{
	t_env	*shlvl;
	int		lvl;

	shlvl = get_env_var(data->env, "SHLVL");
	if (shlvl && shlvl->value)
	{
		lvl = ft_atoi(shlvl->value);
		free(shlvl->value);
		shlvl->value = ft_itoa(lvl + 1);
		upd_env(data);
	}
}

/*
count_vars

Propósito: Cuenta la cantidad de variables en un array de cadenas.

Lógica:
    Itera sobre el array de cadenas `env` hasta encontrar un valor NULL.
    Retorna el número de elementos encontrados.

Comentarios: Es una función auxiliar para calcular el tamaño del entorno.
*/

int	count_vars(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		;
	return (i);
}

/*
copy_envp

Propósito: Copia el entorno (`envp`) en una estructura dinámica.

Lógica:
    Calcula el número de variables usando `count_vars`.
    Reserva memoria para el nuevo array dinámico.
    Copia cada cadena de `envp` al nuevo array.

Comentarios: Se utiliza para inicializar las variables de entorno del shell.
*/

void	copy_envp(t_data *data, char **envp)
{
	int	i;

	if (!envp)
		return ;
	data->envp = ft_calloc(count_vars(envp) + 1, sizeof(char *));
	if (!data->envp)
		return ;
	i = -1;
	while (envp[++i])
		data->envp[i] = ft_strdup(envp[i]);
}

/*
ft_get_pid

Propósito: Obtiene el PID del proceso actual.

Lógica:
    Abre el archivo `/proc/self/stat`.
    Lee el contenido y extrae el PID usando `ft_atoi`.
    Cierra el archivo y retorna el PID.

Comentarios: Facilita el acceso al PID del shell para diversas operaciones.
*/

pid_t	ft_get_pid(void)
{
	int		fd;
	int		pid;
	char	*tmp;

	fd = open("/proc/self/stat", O_RDONLY);
	tmp = get_next_line(fd);
	pid = ft_atoi(tmp);
	free(tmp);
	close(fd);
	return (pid);
}

/*
init_data

Propósito: Inicializa la estructura principal de datos del shell.

Lógica:
    Resetea los valores de la estructura `t_data`.
    Configura las tuberías, el PID, el código de salida previo, y el entorno.
    Llama a `upd_shlvl` para ajustar el nivel del shell.

Comentarios: Prepara la estructura principal del shell antes de su ejecución.
*/

void	init_data(t_data *data, char **envp)
{
	*data = (t_data){0};
	data->input = (t_input){0};
	data->fd[0] = -1;
	data->fd[1] = -1;
	data->l_pipe[0] = -1;
	data->l_pipe[1] = -1;
	data->r_pipe[0] = -1;
	data->r_pipe[1] = -1;
	data->pid = ft_get_pid();
	data->process = ft_itoa(data->pid);
	data->prev_exit_code = ft_itoa(0);
	copy_envp(data, envp);
	envp_to_lst(data);
	upd_shlvl(data);
}

/*
Resumen del archivo

Propósito: Proporciona funciones de inicialización para el shell.

Lógica:
    upd_shlvl: Incrementa el nivel del shell.
    count_vars: Calcula el tamaño del entorno.
    copy_envp: Copia las variables de entorno.
    ft_get_pid: Obtiene el PID del shell.
    init_data: Inicializa la estructura de datos del shell.

Comentarios: Este archivo asegura que el shell esté correctamente preparado
antes de entrar en el bucle principal.
*/
