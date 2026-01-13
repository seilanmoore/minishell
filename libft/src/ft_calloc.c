/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:10:11 by smoore-a          #+#    #+#             */
/*   Updated: 2024/06/12 19:35:39 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;
	size_t			full_size;

	ptr = NULL;
	full_size = count * size;
	ptr = (unsigned char *) malloc(full_size * sizeof(char));
	if (ptr == NULL)
		return (0);
	ft_bzero(ptr, full_size);
	return (ptr);
}
