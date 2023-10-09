/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 09:30:28 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/09 17:40:01 by jmarinho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

// ---------------------------------- INCLUDES ---------------------------------

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <termcap.h>
# include <readline/readline.h>
# include <readline/history.h>

// ---------------------------------- DEFINES ----------------------------------

# define TRUE			1
# define FALSE			0

# define YES			1
# define NO				0

# define EXIT_SUCCESS	0
# define EXIT_FAILURE	1
# define ERROR_FOUND	1
# define EXIT_NO_CMD	2

# define E_QUOTES		"syntax error: unclosed quotes"
# define E_SYNTAX		"syntax error near unexpected token"
# define E_CMD			"error: command not found"
# define E_FILE			"error: no such file or directory"
# define E_MALLOC		"error: malloc"
# define E_PIPE			"error: pipe"
# define E_DUP2			"error: dup2"
# define E_FORK			"error: fork"
# define E_HEREDOC		"error: heredoc"

// ---------------------------------- COLORS ----------------------------------

# define RED 	"\033[1;31m"
# define GREEN 	"\033[1;32m"
# define YELLOW 	"\033[1;33m"
# define BLUE 	"\033[1;34m"
# define PURPLE 	"\033[0;35m"
# define WHITE 	"\033[1;37m"
# define RESET 	"\033[0m"

// ---------------------------------- GLOBAL VARIABLES ----------------------------------

extern int	g_exit_status;

// ---------------------------------- STRUCTS ----------------------------------

typedef enum e_type
{
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR2_IN,
	T_REDIR2_OUT,
	T_QUOTE,
	T_DQUOTE,
	T_OTHER,
	T_COMMAND,
	T_FILE_IN,
	T_FILE_TRUNC,
	T_DELIMITER,
	T_FILE_APPEND,
	T_EMPTY,
}	t_type;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	char			*content;
	t_type			type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	char			**file_in;
	char			**file_tr;
	char			**file_ap;
	char			**heredoc;
	int				fd_in;
	int				fd_out;
	int				index;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_minishell
{
	char			*input;
	char			**envp;
	char			**paths;
	int				**pipe_fd;
	int				n_pipes;
	int				file_error;
	pid_t			pid_heredoc;
	pid_t			*pid;
	t_env			*env_lst;
	t_token			*token_lst;
	t_cmd			*cmd_lst;
}	t_minishell;

// --------------------------------- PROTOTYPES ---------------------------------

// ROOT _________________________________________________________________________

// main.c
void	ft_main_loop(t_minishell *ms);
void	ft_free_all(t_minishell *ms, int exit_flag);

// PARSING ______________________________________________________________________

// parser.c
int		ft_parser(t_minishell *ms, char *input);
int		ft_quote_checker(char *input);

// tokenizer.c
void	ft_tokenizer(t_minishell *ms, char *input);
int		ft_add_token(t_token **token_lst, char *input, t_type type);
int		ft_add_command_token(t_token **token_lst, char *input, t_type type);

// tokenizer_utils.c
t_token *ft_new_token(char *input, t_type type);
void	ft_add_token_back(t_token **token, t_token *new_token);

// syntax_checker.c
int		ft_syntax_checker(t_minishell *ms, t_token *token);

// expander.c
void	ft_expander(t_minishell *ms, t_token *token);
void	ft_expand_command(t_minishell *ms, t_token *token);
char	*ft_get_key(char *cmd);
char	*ft_get_env_value(t_env **env_lst, char *key);
char	*ft_replace_content(char *cmd, char *key, char *value);

// command_table.c
int		ft_command_table_creator(t_minishell *ms);
int		ft_command_table_helper(t_minishell *ms);

// command_table_utils.c
t_cmd	*ft_new_cmd(t_token *first, int n_args);
char	**ft_get_args(t_token *first, int n_args);
char	**ft_add_redirections(t_token *first, t_type type);
void	ft_add_cmd_back(t_cmd **cmd_table, t_cmd *new_cmd);

// ENVIRONMENT __________________________________________________________________

// environment_lst.c
void	ft_init_env_lst(t_env **env, char **envp);
t_env	*ft_new_env(char *key, char *value);
void	ft_add_env_back(t_env **env_lst, t_env *new_env);
char	**ft_get_paths(t_env *env_lst);

// EXECUTION ____________________________________________________________________

// executer.c
void	ft_executer(t_minishell *ms);
void	ft_execute_only_cmd(t_minishell *ms, t_cmd *curr, char *cmd);
void	ft_execute_mult_cmd(t_minishell *ms, t_cmd *curr, char *cmd);
void	ft_execute_cmd_in_child(t_minishell *ms, t_cmd *curr, char *cmd);
void	ft_execute_external(t_minishell *ms, t_cmd *curr, char *cmd);

// redir_handlers.c
void	ft_handle_redir(t_minishell *ms, t_cmd *curr);
void	ft_close_fds(t_cmd *curr);
int		ft_handle_heredoc(t_minishell *ms, char *delimiter);
void	ft_create_heredoc(t_minishell *ms, char *delimiter);
char	*ft_expand_heredoc(t_minishell *ms, char *line);

// pipes_handler.c
void	ft_open_pipes(t_minishell *ms);
void	ft_handle_pipes(t_minishell *ms, t_cmd *curr);
void	ft_close_pipes(t_minishell *ms);

// BUILTINS _____________________________________________________________________

void	ft_cd(t_minishell *ms);
void	ft_echo(t_minishell *ms);
void	ft_env(t_minishell *ms);
void	ft_exit(t_minishell *ms);
void	ft_export(t_minishell *ms);
void	ft_pwd(t_minishell *ms);
void	ft_unset(t_minishell *ms);

// UTILS ________________________________________________________________________

// main_utils.c
int		ft_perror(t_minishell *ms, char *error, int free_flag);
int		ft_perror_fd(t_minishell *ms, char *filename, t_type file_type);
int		ft_everything_is_space(char *str);

// parsing_utils.c
int		ft_is_space(char c);
int		ft_len_until_match(char *input, char *match);
int		ft_is_cmd_or_file(t_type type);
int		ft_count_redir(t_token *first, t_type type);

// execution_utils.c
int		ft_cmd_has_redir(t_cmd *cmd);
int		ft_count_pipes(t_cmd *cmd_lst);
void	ft_set_cmd_index(t_minishell *ms);

// free_utils.c
void	ft_free_token_lst(t_token **token_lst);
void	ft_free_cmd_lst(t_cmd **cmd_table);
void	ft_free_env_lst(t_env **env_lst);
void	ft_free_str_array(char **str_array);
void	ft_free_pipes(t_minishell *ms);

// builtins_utils.c
char 	*ft_find_env(t_env *env_lst, char *find);
void	ft_update_env(t_env **env_lst, char *key, char *update);
char 	ft_strchr2(const char *str, char c);
void	ft_lstadd_back2(t_env *env_lst, t_env *new_envi);
bool 	ft_not_forkable(t_minishell *ms);


// SIGNALS ________________________________________________________________________

// signals.c
void	ft_signals(void);
void	ft_signals_heredoc(void);
void	ft_signals_child(void);
void	ft_signals_ignore(void);

// handlers.c
void	ft_handler_sigint(int signum);
void	ft_handler_heredoc(int signum);
void	ft_handler_child(int signum);
void	ft_handler_sigquit(int signum);

# endif
