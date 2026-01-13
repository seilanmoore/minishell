/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:42:05 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/19 17:03:14 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/* int	main(void) //ft_bzero
{
	char	str1[30] = "Hello my name";
	char	str2[30] = "Hello my name";

	ft_bzero(str1, 5);
	printf("Using ft_bzero, the string looks like this: %s.\n", str1);
	bzero(str2, 5);
	printf("Using bzero, the string looks like this: %s.\n", str2);
	return (0);
} */

/* int	main(void) //ft_isalnum
{
	printf("Using ft_isalnum \'%c\' returns: %d.\n",
		FTALNUM, ft_isalnum(FTALNUM));
	printf("Using ft_isalnum \'%c\' returns: %d.\n",
		FTALNUM, isalnum(FTALNUM));
	return (0);
} */

/* int	main(void) //ft_isalpha
{
	printf("Using ft_isalpha \'%c\' returns: %d.\n",
		FTCHAR, ft_isalpha(FTCHAR));
	printf("Using isalpha \'%c\' returns: %d.\n",
		FTCHAR, isalpha(FTCHAR));
	return (0);
} */

/* int	main(void) //ft_isascii
{
	printf("Using ft_isascii \'%c\' returns: %d.\n",
		FTALNUM, ft_isascii(FTALNUM));
	printf("Using ft_isascii \'%c\' returns: %d.\n",
		FTALNUM, isascii(FTALNUM));
	return (0);
} */

/* int	main(void) //ft_isdigit
{
	printf("Using ft_isdigit \'%c\' returns: %d.\n",
		FTDIGIT, ft_isdigit(FTDIGIT));
	printf("Using isdigit \'%c\' returns: %d.\n",
		FTDIGIT, isdigit(FTDIGIT));
	return (0);
} */

/* int	main(void) //ft_isprint
{
	printf("Using ft_isprint \'%c\' returns: %d.\n",
		FTALNUM, ft_isprint(FTALNUM));
	printf("Using ft_isprint \'%c\' returns: %d.\n",
		FTALNUM, isprint(FTALNUM));
	return (0);
} */

/* int	main(void) //ft_memcpy
{
	char	src[30] = "Start stop";

	ft_memcpy(src + 2, src, 3);
	printf("Using memcpy, the string looks like this: %s.\n", src);
	return (0);
} */

/* int	main(void) //ft_memmove
{
	char	src[] = "0123456789";
	char	src1[] = "0123456789";

	printf("The prev srt is: %s.\n", src);
	ft_memmove(src, src + 3, 2);
	printf("The next srt is: %s.\n", src);
	printf("The prev srt is: %s.\n", src1);
	memmove(src1, src1 + 3, 2);
	printf("The next srt is: %s.\n", src1);
	return (0);
} */

/* int	main(void) //ft_memset
{
	char	str1[30] = "";
	char	str2[30] = "";

	printf("Using ft_memset, the string looks like this: %s.\n",
		ft_memset(str1, 'B', 5));
	printf("Using memset, the string looks like this: %s.\n",
		memset(str2, 'B', 5));
	return (0);
} */

/* int	main(void) //ft_strlcpy
{
	char	*src1;
	char	dst1[0] = "";
	char	*src2;
	char	dst2[0] = "";

	src1 = "aaa";
	src2 = "aaa";
	ft_strlcpy(dst1, src1, 0);
	printf("Using ft_strlcpy, the string looks like this: %s. "
		"And the size of the src is : %lu.\n", dst1, ft_strlcpy(dst1, src1, 0));
	strlcpy(dst2, src2, 0);
	printf("Using strlcpy, the string looks like this: %s. "
			"Size of the src is : %lu.\n",
			dst2,
			strlcpy(dst2, src2, 0));
	return (0);
} */

/* int	main(void) //ft_strlen
{
	char	*str = "fefefefe";

	printf("Using ft_strlen, the lengnth is: %lu.\n", ft_strlen(str));
	printf("Using strlen, the lengnth is: %lu.\n", strlen(str));
	return (0);
} */

/* int	main(void) //ft_strlcat
{
	char	dest[10] = "A";
	size_t	full_len = ft_strlcat(dest, "lorem ipsum dolor sit amet", 0);

	printf("Concatenated string: \"%s\"\n", dest);
	printf("Total size if not truncated: %lu\n", full_len);
	return (0);
} */

/* int	main(void) //ft_toupper
{
	char	str[] = "What eVeR.";
	int		i = 0;

	printf("Using ft_toupper \'%s\'\n", str);
	while (str[i])
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
	printf("Returns: %s\n", str);
	return (0);
} */

/* int	main(void) //ft_tolower
{
	char	str[] = "What eVeR.";
	int		i = 0;

	printf("Using ft_tolower \'%s\'\n", str);
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	printf("Returns: %s\n", str);
	return (0);
} */

/* int	main(void) //ft_strchr
{
	char	str[] = "tes7ñte";

	printf("Using ft_strchr want to find \'%c\' in the"
		" string \'%s\'\n", 'a', str);
	printf("Returns: %p\n", ft_strchr(str, -61));
	printf("Using strchr want to find \'%c\' in the"
		" string \'%s\'\n", 'a', str);
	printf("Returns: %p\n", strchr(str, -61));
	char	z[100];

	z[0] =  -61;

	printf("%s, %d, %d\n", z, z[0], (unsigned char)z[0]);
	return (0);
} */

/* int	main(void) //ft_strrchr
{
	char	str[] = "tes7ñte";

	printf("Using ft_strchr want to find \'%c\' in the"
		" string \'%s\'\n", 'a', str);
	printf("Returns: %p\n", ft_strrchr(str, 'e'));
	printf("Using strchr want to find \'%c\' in the"
		" string \'%s\'\n", 'a', str);
	printf("Returns: %p\n", strrchr(str, 'e'));
	char	z[100];

	z[0] =  -61;

	printf("%s, %d, %d\n", z, z[0], (unsigned char)z[0]);
	return (0);
} */

/* int	main(void) //ft_strncmp
{
	char	str[] = "C";
	char	str1[] = "";

	printf("Using ft_strncmp return: \'%d\'\n", ft_strncmp(str, str1, 0));
	printf("Using strncmp return: \'%d\'\n", strncmp(str, str1, 0));
	return (0);
} */

/* int	main(void) //ft_memchr
{
	char	str[] = "/|\x12\xff\x09\0\x42\042\0\42|\\";

	printf("Using ft_memchr, mem dir is:	%p\n",
		ft_memchr(str, '\0', 12));
	printf("Using memchr, mem dir is:   	%p\n",
		memchr(str, '\0', 12));
	return (0);
} */

/* int	main(void) //ft_memcmp
{
	char	str1[] = "/|\x12\xff\0\x42\042\0\42|\\";
	char	str2[] = "/|\x12\xff\0\x42\042\0\42|\\";

	printf("Using ft_memchr, the diff is:	%d\n",
		ft_memcmp(str1, str2, 12));
	printf("Using memchr, the diff is:   	%d\n",
		memcmp(str1, str2, 12));
	return (0);
} */

/* int	main(void) //ft_strnstr
{
	char	str1[] = "aaabcdbc";
	char	str2[] = "aabcd";

	printf("Using ft_strnstr:	%s\n",
		ft_strnstr(str1, str2, 7));
	printf("Using strnstr:   	%s\n",
		strnstr(str1, str2, 7));
	return (0);
} */

/* int	main(void) //ft_atoi
{
	printf("Passed the string with ft_atoi\n"
		"Returns:	\'%d\'\n", ft_atoi("1209"));
	printf("Passed the string with atoi\n"
		"Returns:	\'%d\'\n", atoi("1209"));
	return (0);
} */

/* int	main(void) //ft_calloc
{
	printf("Calling ft_calloc: \n"
		"Returns:	\'%p\'\n", ft_calloc(5, 4));
	printf("Calling calloc: \n"
		"Returns:	\'%p\'\n", calloc(5, 4));
	return (0);
} */

/* int	main(void)
{
	char	str[] = "lorem ipsum dolor sit amet";

	printf("Using ft_substr:	%1$s\nPointer:    %1$p\n",
		ft_substr(str, 20, 10));
	return (0);
} */

/* int	main(void) //ft_strjoin
{
	char	str[] = "Nico ";
	char	str1[] = "esta malito";

	printf("Using ft_strjoin return:\n\"%s\"\n", ft_strjoin(str, str1));
	return (0);
} */

/* int	main(void) //ft_strtrim
{
	char	str[] = "lorem ipsum dolor sit amet";

	printf("Using ft_strtrim return:\n\"%s\"\n", ft_strtrim(str, "aemt"));
	return (0);
} */

/* int	main(void) //ft_split
{
	char	str[] = "Hola muy buenas tardes";
	char	**mtrx = ft_split(str, ' ');
	int		i = -1;

	while (++i < 4)
		printf("The %dth word is \'%s\'\n", i + 1, mtrx[i]);
	return (0);
} */

/* int	main(void) //ft_itoa
{
	int	n = 9;

	printf("For the nb \'%d\' returns:	\'%s\'\n", n, ft_itoa(n));
	return (0);
} */

/* int	main(int argc, char **argv) //ft_putstr_fd
{
	int	fd;

	if (!argc)
		return (-1);
	fd = open(argv[1], O_RDWR);
	ft_putstr_fd("\"Hello\"", fd);
	close(fd);
	return (0);
} */

/* int	main(void) //lst_new
{
	t_list *node;
	int content = 42;

	node = ft_lstnew(&content);
	if (node == NULL)
	{
		printf("Failed to allocate memory for node\n");
		return (1);
	}
	if (node->content != NULL)
		printf("Content of the node: %d\n", *(int *)(node->content));
	else
		printf("Node content is NULL\n");
	if (node->next != NULL)
		printf("Next node exists\n");
	else
		printf("Next node is NULL\n");
	free(node);
	return (0);
} */

/* int	main(void) //ft_lstadd_front_bonus
{
	t_list	*node1;
	t_list	*node2;
	t_list	*current;
	t_list	*new_node;
	char	a[] = " My";
	char	b[] = " Name";
	char	c[] = "Hello";
	
	node1 = ft_lstnew(&a);
	node2 = ft_lstnew(&b);
	node1->next = node2;
	new_node = ft_lstnew(&c);
	current = node1;
	while (current)
	{
		printf("%s", (char *)current->content);
        current = current->next;
	}
	ft_lstadd_front(&node1, new_node);
	current = node1;
	while (current)
	{
		printf("%s", (char *)current->content);
        t_list *tmp = current;
        current = current->next;
        free(tmp);
	}
	return (0);
} */
