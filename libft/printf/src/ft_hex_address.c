/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_address.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 09:06:39 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/19 17:03:34 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int	hex_conv(size_t n)
{
	size_t	i;
	size_t	len;
	char	nbr[16];

	i = 0;
	while (n > 0)
	{
		if (n % 16 < 10)
			nbr[i] = '0' + (n % 16);
		else
			nbr[i] = 'a' + (n % 16) - 10;
		n /= 16;
		i++;
	}
	len = i;
	while (i-- > 0)
	{
		if (put_char(nbr[i]) == -1)
			return (-1);
	}
	return (ft_bzero(nbr, 16), len);
}

int	ft_hex_address(size_t address)
{
	int		len;

	if (!address)
	{
		if (put_str("0x0") == -1)
			return (-1);
		return (3);
	}
	if (put_str("0x") == -1)
		return (-1);
	len = 2;
	len += hex_conv(address);
	return (len);
}
