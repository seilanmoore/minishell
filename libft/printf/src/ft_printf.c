/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 09:55:29 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/19 17:03:34 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

static const char	*read_str(va_list *ap, const char *p, int *count)
{
	int	add;

	add = 0;
	if (*p != '%')
		add = put_char(*p);
	else
	{
		p++;
		add = ft_conversion(*p, *ap);
	}
	if (add == -1)
	{
		*count = -1;
		return (NULL);
	}
	p++;
	*count = *count + add;
	return (p);
}

int	ft_printf(const char *format, ...)
{
	const char	*p;
	va_list		ap;
	int			count;

	if (write(1, "", 0) == -1)
		return (-1);
	count = 0;
	va_start(ap, format);
	p = format;
	while (*p)
	{
		p = read_str(&ap, p, &count);
		if (count == -1)
		{
			va_end(ap);
			return (-1);
		}
	}
	va_end(ap);
	return (count);
}
