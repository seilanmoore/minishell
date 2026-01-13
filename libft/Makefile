# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 15:26:15 by smoore-a          #+#    #+#              #
#    Updated: 2024/06/08 14:23:04 by smoore-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = clang

CFLAGS = -Wall -Werror -Wextra -O3

INCLUDE = -Iinclude

HEADER = include/

RM = rm -rf

SRC_DIR = src/

OBJ_DIR = obj/

BONUS = bonus/

PRINTF = printf/

GNL = get_next_line/

SRC = ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint \
	ft_strlen ft_memset ft_bzero ft_memcpy ft_memmove \
	ft_strlcpy ft_strlcat ft_toupper ft_tolower ft_strchr \
	ft_strrchr ft_strncmp ft_memchr ft_memcmp ft_strnstr \
	ft_atoi ft_calloc ft_strdup ft_substr ft_strjoin \
	ft_strtrim ft_split ft_itoa ft_strmapi ft_striteri \
	ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd \
	ft_lstnew_bonus ft_lstadd_front_bonus \
	ft_lstsize_bonus ft_lstlast_bonus \
	ft_lstadd_back_bonus ft_lstdelone_bonus \
	ft_lstclear_bonus ft_lstiter_bonus \
	ft_lstmap_bonus

PRINTF_SRC = ft_printf ft_conversion ft_hex_address ft_puthex_fd \
	ft_uitoa ft_printf_itoa ft_printf_utils

GNL_SRC = get_next_line get_next_line_utils

SRC_FILES = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC)))

OBJ_FILES = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC)))

PRINTF_SRC_F = $(addprefix $(PRINTF)$(SRC_DIR), $(addsuffix .c, $(PRINTF_SRC)))

PRINTF_OBJ_F = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(PRINTF_SRC)))

GNL_SRC_F = $(addprefix $(GNL)$(SRC_DIR), $(addsuffix .c, $(GNL_SRC)))

GNL_OBJ_F = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(GNL_SRC)))

all: $(NAME)

$(NAME): $(OBJ_FILES) $(PRINTF_OBJ_F) $(GNL_OBJ_F)
	ar rcs $@ $^
	@echo "$(NAME) compiled"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)libft.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@ 
	@echo "$< compiled"

$(OBJ_DIR)%.o:	$(PRINTF)$(SRC_DIR)%.c $(HEADER)ft_printf.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "$< compiled"

$(OBJ_DIR)%.o: $(GNL)$(SRC_DIR)%.c $(HEADER)get_next_line.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "$< compiled"

clean:
	$(RM) $(OBJ_DIR)
	@echo "Object files removed"

fclean: clean
	$(RM) $(NAME)
	@echo "$(NAME) removed"

re: fclean all

.PHONY: all clean fclean re

ifndef VERBOSE
.SILENT:
endif