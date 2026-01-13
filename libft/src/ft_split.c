/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 22:16:43 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/19 17:03:14 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static size_t	count_items(const char *s, char c)
{
	size_t	items;

	items = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			items++;
		while (*s != c && *s)
			s++;
	}
	return (items);
}

static char	**cpy_to_mtrx(char const *s, char c, char **mtrx, size_t i)
{
	size_t	item_len;

	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			if (!ft_strchr(s, c))
				item_len = ft_strlen(s);
			else
				item_len = ft_strchr(s, c) - s;
			mtrx[i++] = ft_substr(s, 0, item_len);
			if (!mtrx[i - 1])
			{
				while (i > 0)
					free(mtrx[--i]);
				free(mtrx);
				return (NULL);
			}
			s += item_len;
		}
	}
	mtrx[i] = NULL;
	return (mtrx);
}

char	**ft_split(char const *s, char c)
{
	char	**mtrx;

	if (!s)
		return (NULL);
	mtrx = (char **)malloc((count_items(s, c) + 1) * sizeof(char *));
	if (!mtrx)
		return (NULL);
	return (cpy_to_mtrx(s, c, mtrx, 0));
}
