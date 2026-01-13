/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:03:33 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/19 17:03:14 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strdup(const char *s1)
{
	unsigned char	*str;
	size_t			s1_len;

	s1_len = ft_strlen(s1) + 1;
	str = (unsigned char *) malloc(s1_len * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_strlcpy((char *) str, s1, s1_len);
	return ((char *) str);
}
