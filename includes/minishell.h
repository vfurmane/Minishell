/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:20:33 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/25 15:05:59 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <term.h>
# include <errno.h>
# include <ncurses.h>
# include <termios.h>
# include "builtin.h"
# include "define.h"
# include "utils.h"
# include "termcaps.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# if __APPLE__
#  ifndef ARG_MAX
#   define ARG_MAX 131072
#  endif
# else
#  include <linux/limits.h>
#  ifndef __APPLE__
#   define __APPLE__ 0
#  endif
# endif

typedef int	(*t_builtin)(t_config*, char**, int);

typedef enum e_separator
{
	EOCMD,
	REDIR_LEFT,
	REDIR_APPEND,
	REDIR_RIGHT,
	PIPE,
	BRACKET_TO,
	BRACKET_FROM
}			t_separator;

typedef struct s_cmd
{
	struct s_cmd	*next;
	char			*str;
	t_separator		separator;
	int				fd[2];
	int				file;
	int				file_to;
	int				file_from;
	int				from_to;
}				t_cmd;

typedef struct s_kvpair
{
	struct s_kvpair	*next;
	char			*key;
	char			*value;
}				t_kvpair;

typedef struct s_dlist
{
	struct s_dlist	*next;
	struct s_dlist	*previous;
	void			*content;
}				t_dlist;

typedef struct s_config
{
	int				quit;
	t_kvpair		*envp_list;
	char			**envp;
	int				fd[2];
	struct termios	termios_backup;
	char			*prompt;
	t_dlist			*history;
	unsigned char	exit_code;
	int				start_column;
}				t_config;

typedef struct s_icanon
{
	int				column;
	int				line_i;
	char			*line;
	unsigned char	buffer[4];
}				t_icanon;

typedef struct s_cmd_arg
{
	int			i;
	int			backslash;
	char		*str;
	char		quote;
}				t_cmd_arg;

int					ft_init_args_tree(t_config *shell_c, char *const buffer);

int					ft_handle_command(t_cmd *cmd, t_config *shell_c,
						int pipefd[2]);
int					ft_recursiv_command(t_cmd *cmd, t_config *shell_c,
						int pipe_in, int std_out);

int					ft_parse_envp(char **envp, t_config *shell_c);
char				*ft_replace_with_env(t_config *shell_c, const char *str,
						int *str_i);
char				*ft_getenv(t_kvpair *envp_list, const char *name);
int					ft_parse_envp(char **envp, t_config *shell_c);

int					ft_execve(const char *filename, char *const argv[],
						char *const envp[]);
int					ft_exec(t_config *shell_c, char **command);

void				free_shell(t_config *shell_c);
void				free_neo(char **str);
void				free_neo_content(char **str);
void				free_all_cmd(t_cmd *cmd);

int					ft_insert_char(t_icanon *icanon);
int					ft_delete_char(char *str, int column);
int					ft_rewrite_line(t_icanon *icanon, int move_cursor);

int					ft_display_prompt(char *prompt);
int					ft_prompt(t_config *shell_c);
char				*ft_fix_openfiles(t_config *shell_c, char *const buffer,
						t_cmd *cmd, int *error);
int					pars_files(char *const buffer, t_config *shell_c,
						t_cmd *cmd, int *i);
char				*ft_cmd_argdup(t_config *shell_c, const char *cmd);

int					ft_stderr_message(const char *str1, const char *str2,
						const char *str3, int ret);

int					ft_route_command(const char *command, char **args,
						char **line, t_config *shell_c);
int					ft_route_file_to(const char *file_name, t_config *shell_c,
						int happen);
int					ft_write_pipe(const char *key, const char *value1,
						const char *value2, int pipefd);
int					ft_route_file_from(const char *file_name,
						t_config *shell_c);

char				**ft_split_cmd(t_config *shell_c, const char *cmd);

int					ft_update_env(t_config *shell_c);
int					ft_del_env(t_config *shell_c, char *str);
int					ft_add_env(t_config *shell_c, const char *str);

int					ft_update_shell(t_config *shell_c);

#endif
