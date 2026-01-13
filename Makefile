# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/27 20:48:30 by smoore-a          #+#    #+#              #
#    Updated: 2025/01/20 19:25:11 by smoore-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

INCLUDE = -Iinclude -Ilibft/include -I/usr/include

HEADER = minishell.h

CC = clang

CFLAGS = -g -Wall -Werror -Wextra -O0 # -O0 -fsanitize=address

L_FLAGS = -Llibft -lft -lreadline

LIBFT = libft/libft.a

RM = rm -rf

SRC_DIR = src/

OBJ_DIR = obj/

SRC = main init free_func command_path environment env_utils \
	parser parser_checks1 parser_checks2 parser_types \
	tokenizer tokenizer_utils expand expand_utils utils \
	command command_utils locals syntax syntax_circles \
	cd_builtin export_builtin unset_builtin exit_builtin env_builtin \
	pwd_builtin echo_builtin close_files expand_later open_pipe handle_io \
	execute_io executers handle_error concatenate_token \
	open_files heredoc j_bool_utils j_expand_terms j_free_data_type \
	j_history j_print_utils j_string_utils j_env_utils_2 minishell \
	history_builtin

UTILS =

OBJ_FILES = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC))) \
	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(UTILS)))

VPATH = src:include

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_FILES)
	$(CC) $(CFLAGS) $(INCLUDE) $^ $(L_FLAGS) -o $@
	@echo "$(NAME) compiled"

$(OBJ_DIR)%.o: %.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "$< compiled"

$(LIBFT):
	@make all -C libft
	@echo "$(LIBFT) compiled"

#bonus:
#	@make all -C bonus

clean:
	$(RM) $(OBJ_DIR)
	@echo "Object files removed"
	@make clean -C libft
	@echo "Libft object files removed"
#	@make clean -C bonus
#	@echo "Bonus object files removed"

fclean: clean
	$(RM) $(NAME)
	@echo "$(NAME) removed"
	$(RM) $(LIBFT)
	@echo "$(LIBFT) removed"
#	$(RM) $(BONUS)
#	@echo "$(BONUS) removed"

re: fclean all

nocflag:
	$(MAKE) $(LIBFT)
	$(MAKE) CFLAGS="" $(NAME)

.PHONY: all clean fclean re bonus nocflag

ifndef VERBOSE
.SILENT:
endif
