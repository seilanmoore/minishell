/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 13:37:04 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/19 17:03:34 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int	ft_puthex_fd(unsigned int n, int low_upper)
{
	size_t	i;
	size_t	len;
	char	nbr[8];

	if (n == 0)
		return (put_char('0'));
	i = 0;
	while (n > 0)
	{
		if (n % 16 < 10)
			nbr[i] = '0' + (n % 16);
		else if (!low_upper)
			nbr[i] = 'a' + (n % 16) - 10;
		else if (low_upper)
			nbr[i] = 'A' + (n % 16) - 10;
		n /= 16;
		i++;
	}
	len = i;
	while (i-- > 0)
	{
		if (put_char(nbr[i]) == -1)
			return (-1);
	}
	return (ft_bzero(nbr, 8), len);
}
