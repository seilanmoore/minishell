/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:22:01 by smoore-a          #+#    #+#             */
/*   Updated: 2024/09/27 14:01:58 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned char	*res_str;
	size_t			full_size;

	full_size = ft_strlen(s1) + ft_strlen(s2) + 1;
	res_str = (unsigned char *) malloc(sizeof(char) * full_size);
	if (!res_str)
		return (NULL);
	ft_strlcpy((char *) res_str, s1, ft_strlen(s1) + 1);
	ft_strlcat((char *) res_str, s2, full_size);
	return ((char *) res_str);
}
