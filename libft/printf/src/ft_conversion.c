/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:33:58 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/19 17:03:34 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int	ft_conversion(char format, va_list ap)
{
	if (format == 'c')
		return (put_char(va_arg(ap, int)));
	else if (format == 's')
		return (put_str(va_arg(ap, char *)));
	else if (format == 'p')
		return (ft_hex_address((size_t)va_arg(ap, void *)));
	else if (format == 'd' || format == 'i')
		return (int_itoa(va_arg(ap, int)));
	else if (format == 'u')
		return (ft_uitoa(va_arg(ap, unsigned int)));
	else if (format == 'x')
		return (ft_puthex_fd(va_arg(ap, unsigned int), 0));
	else if (format == 'X')
		return (ft_puthex_fd(va_arg(ap, unsigned int), 1));
	else if (format == '%')
		return (put_char('%'));
	else
		return (-1);
}
