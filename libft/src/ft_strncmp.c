/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:45:10 by smoore-a          #+#    #+#             */
/*   Updated: 2024/09/24 11:32:21 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	if (n <= 0)
		return (-1);
	if (!s1 && s2)
		return (-1);
	if (!s2 && s1)
		return (1);
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (*str1 == '\0' || *str2 == '\0')
		return (*str1 - *str2);
	while ((*str1 || *str2) && n--)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	return (*(str1 - 1) - *(str2 - 1));
}
