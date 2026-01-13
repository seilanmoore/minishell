/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:54:05 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/19 17:03:14 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_atoi(const char *str)
{
	unsigned char	*ptr;
	int				sign;
	int				nbr;

	nbr = 0;
	sign = 1;
	ptr = (unsigned char *) str;
	while (*ptr == ' ' || *ptr == '\t' || *ptr == '\n'
		|| *ptr == '\v' || *ptr == '\f' || *ptr == '\r')
		ptr++;
	if (*ptr == '+' || *ptr == '-')
	{
		if (*ptr == '-')
			sign *= -1;
		ptr++;
	}
	if (*ptr == '+' || *ptr == '-')
		return (0);
	while (*ptr != '\0' && *ptr >= '0' && *ptr <= '9')
	{
		nbr = nbr * 10 + (*ptr - '0');
		ptr++;
	}
	nbr *= sign;
	return (nbr);
}
