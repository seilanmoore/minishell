/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:17:44 by smoore-a          #+#    #+#             */
/*   Updated: 2025/01/20 22:01:19 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>
# include <sys/stat.h>
# include <dirent.h>

# define MS "minishell: "
# define EMPTY_PATH "PATH variable is empty"
# define NO_PATH "PATH variable not found"
# define NOT_FOUND "command not found"
# define ERROR "error "
# define PATH_EXIST "No such a file or directory"
# define PERMIT "Permission denied"
# define IS_DIR "Is a directory"
# define NOT_DIR "Not a directory"

# define EXPORT "export: "
# define EXPORT_ID "not a valid identifier"

# define CD "cd: "
# define CD_OPT "no options allowed"
# define CD_ARG "too many arguments"
# define CD_HOME "HOME not set"

# define ECHO "echo: "
# define ECHO_OPT "not valid option"
# define ECHO_OPTS "too many options"

# define CMD 100		// cmd
# define OPTION 101		// cmd option
# define ARG 102		// argument
# define PIPE 103 		// |
# define LEFT 104 		// <
# define RIGHT 105 		// >
# define LEFTT 106 		// <<
# define RIGHTT 107 	// >>
# define FILE 108		// file
# define HERE 109 		// heredoc
# define LOCAL 110 		// variable=value
# define LOCAL_VAL 111	// " value "
# define NO_QUOTE 120
# define S_QUOTE 121 	// ''
# define D_QUOTE 122 	// ""

extern int				g_signal;

void	signal_handler(int sig);

typedef struct s_tokens	t_token;

typedef struct s_command
{
	char				*cmd;
	char				**args;
	int					builtin;
	t_token				*token;
	struct s_command	*next;
}	t_cmd;

typedef struct s_tokens
{
	char		*token;
	int			type;
	int			quote;
	int			end_space;
	t_cmd		*cmd;
	t_token		*opt;
	t_token		*arg;
	t_token		*prev;
	t_token		*next;
}	t_token;

typedef struct s_input
{
	char		*raw_line;
	t_token		*tokens;
	t_cmd		*command;
}	t_input;

typedef struct s_var
{
	char	*aux;
	char	*aux1;
	int		i;
}	t_var;

typedef struct s_environment
{
	char					*variable;
	char					*value;
	struct s_environment	*next;
}	t_env;

typedef struct s_pipe
{
	int	fd[2];
}	t_pipe;

typedef struct s_data
{
	int			fd[2];
	int			l_pipe[2];
	int			r_pipe[2];
	int			here_pipe[2];
	char		*heredoc;
	char		**envp;
	char		**paths;
	char		*user;
	char		*cwd;
	char		*prompt;
	char		*history;
	t_token		*last_cmd;
	t_token		*first_token;
	int			n_cmd;
	int			n_pipe;
	int			n_files;
	int			in_cmd;
	int			in_arg;
	int			in_local;
	int			status;
	int			exit_code;
	char		*prev_exit_code;
	char		*process;
	pid_t		pid;
	pid_t		*pids;
	t_env		*locals;
	t_env		*env;
	t_input		input;
	struct stat	stat;
}	t_data;

void	handle_quit(int sig);
void	handle_signal(int sig);

// init
void	init_data(t_data *data, char **envp);

//minishell
void	minishell(t_data *data);

// Free data types
void	free_array(char ***array);
void	free_local(t_data *data);
void	free_env_lst(t_data *data);
void	free_cmds(t_data *data);
void	free_lst(t_list **lst);

// free_func
void	ft_free(void **str);
void	free_environment(t_data *data);
void	free_tokens(t_data *data);
void	free_data(t_data *data);

//environment
void	envp_to_lst(t_data *data);
void	envp_to_array(t_data *data);

//env_utils
t_env	*get_env(t_env *l_variables, char *l_variable);
t_env	*get_env_var(t_env *env, char *variable);
t_env	*new_variable(char *variable, char *value);
t_env	*last_variable(t_env *lst);
void	del_env(t_env **env, char *variable);

// locals
void	print_locals(t_data *data);
int		locals(t_data *data);

//parser
void	parser(t_data *data);
void	access_to_types(t_data *data, int target, int type);
void	type_checks(t_data *data, t_token *ptr, int i);

//command
void	parse_cmd_opt(t_data *data);

//command_path
void	assign_paths(t_data *data);

//command_utils
void	add_back_cmd(t_cmd **lst, t_cmd *node);
t_cmd	*new_cmd(t_token *token, char **arguments, int builtin);
t_cmd	*last_cmd(t_cmd *lst);

//syntax
void	syntax_msg(char *wildcard);
int		is_redirection(int type);
int		is_word(int type);
int		syntax_error(t_data *data);

//syntax_circles
int		circle_1(t_token *token);
int		circle_2(t_token *token, t_token *prev);
int		circle_3(t_token *token, t_token *prev);
int		circle_4(t_token *token, t_token *prev);

// tokenizer
void	tokenizer(t_data *data);
//tokenizer_utils
int		end_space(t_var *var);
void	set_prev_token(t_data *data);
t_token	*new_token(void *token, int type, int quote, int end_space);
t_token	*last_token(t_token *lst);

//concatenate_token
void	concatenate_tokens(t_data *data);

// parser_checks2
int		check_cmds(t_data *data, t_token *ptr, int i);

// types
void	assign_types(t_data	*data);
void	remove_equal(t_data *data);
void	assign_opt_arg(t_data *data);

// expand_utils

char	*get_dollar_value(t_data *data, char *variable);
char	*extract_id(char *token);

// expand
void	expand_terms(t_data *data, t_list **lst);
char	*lst_str_join(t_list *lst);
void	expand(t_data *data);

// expand_later
void	expand_later(t_data *data, char **line);

//builtin
int		exit_builtin(t_data *data, t_cmd *cmd);
int		unset_builtin(t_data *data, t_cmd *cmd);
int		cd_builtin(t_data *data, t_cmd *cmd);
int		export_builtin(t_data *data, t_cmd *cmd);
int		echo_builtin(t_cmd *cmd);
int		pwd_builtin(t_data *data);
int		env_builtin(t_data *data);
int		history_builtin(void);

char	*cwd_compress(t_data *data);

int		lst_size(t_token *lst);

void	add_back_token(t_token **lst, t_token *node);

void	add_back_variable(t_env **lst, t_env *node);
int		env_size(t_env *lst);

void	upd_env(t_data *data);
void	print_env(t_data *data);

// utils
int		ft_strcmp(const char *str1, const char *str2);
void	print_types(t_data *data);
void	print_cmd_array(t_data *data);
char	*str_replace(char *haystack, char *needle, char *replace);
void	print_msg(t_data *data, char *msg, int status);
char	*rev_split(char **array);
void	print_array(char **array);
int		valid_char(char c);
int		valid_ident(char *str);
char	*get_envp_var(char **envp, char *var);
int		no_word(int c);
int		is_redir(int c);
int		is_space(int c);
void	print_locals(t_data *data);
char	**split_token(char *token);
void	check_new_var(t_env **lst, t_env *new_var, char *var, char *value);

// handle_error
int		handle_errno(char *wildcard);
int		execve_error(t_data *data, t_cmd *cmd);
int		id_error(t_data *data, char *arg, char *variable, int exp);
//int		cmd_error(t_data *data, int status, int print);

// open_files
int		open_files(t_data *data);

//heredoc
int		write_heredoc(t_data *data);

// history
void	get_history(void);
void	save_history(void);

//Expand terms
t_list	*split_terms(char *line);

// dir get
char	*get_dir(char *path);

//String utils
char	*type_to_char(int type);

//close_files
void	close_infiles(t_data *data);
void	close_parent_files(t_data *data);

//open_pipe
int		change_pipe(t_data *data);
int		open_r_pipe(t_data *data);

// handle_io
int		handle_io(t_data *data);

//execute_io
int		execute(t_data *data);

//execute
int		builtin_out(t_data *data, t_cmd *cmd, int fork);
int		builtin_redir(t_data *data, t_cmd *cmd);
void	cmd_out(t_data *data, t_cmd *command);

#endif
