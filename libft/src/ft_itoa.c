/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:40:52 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/19 17:03:14 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static size_t	count_digit(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static	char	*int_min(void)
{
	char	*nbr;

	nbr = ft_strdup("-2147483648");
	if (!nbr)
		return (NULL);
	return (nbr);
}

char	*ft_itoa(int n)
{
	int		sign;
	size_t	len;
	char	*nbr;

	sign = 0;
	len = count_digit(n);
	if (n == -2147483648)
		return (int_min());
	nbr = (char *)malloc((len + 1) * sizeof(char));
	if (!nbr)
		return (NULL);
	nbr[len] = '\0';
	if (n < 0)
	{
		n = -n;
		sign = 1;
	}
	while (len-- > 0)
	{
		nbr[len] = '0' + (n % 10);
		n /= 10;
	}
	if (sign)
		nbr[0] = '-';
	return (nbr);
}
