/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:20:33 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/21 20:25:10 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <term.h>
#include <errno.h>
#include <ncurses.h>
#include <termios.h>
#include "builtin.h"
#include "define.h"
#include "utils.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#if __APPLE__
#ifndef ARG_MAX
#define ARG_MAX 131072
#endif
#else
#include <linux/limits.h>
#ifndef __APPLE__
#define __APPLE__ 0
#endif
#endif

typedef enum		e_separator
{
	EOCMD,
	REDIR_LEFT,
	REDIR_APPEND,
	REDIR_RIGHT,
	PIPE
}					t_separator;

typedef struct		s_cmd
{
	struct s_cmd *next;
	char *str;
	t_separator separator;
	int fd[2];
}					t_cmd;

typedef struct		s_kvpair
{
	struct s_kvpair	*next;
	char			*key;
	char			*value;
}					t_kvpair;

typedef struct		s_config
{
	int				quit;
	t_kvpair		*envp_list;
	char			**envp;
	int				fd[2];
}					t_config;

typedef struct		s_icanon
{
	int				column;
	int				line_i;
	char			*line;
	unsigned char	buffer[3];
}					t_icanon;

int					ft_handle_command(t_cmd *cmd, t_config *shell_c,
					int pipefd[2]);

char				*ft_exportenv(const char *str, int *str_i,
					char **environment);
char				*ft_getenv(char **env, char *str);


int					ft_execve(const char *filename, char *const argv[],
					char *const envp[]);
int					ft_exec(char **command, char **environement);

int					ft_insert_char(t_icanon *icanon);
int					ft_delete_char(char *str, int column);
int					ft_rewrite_line(t_icanon *icanon);

int					ft_prompt(t_config *shell_c, int pipefd[2]);

int					ft_read_icanon(t_config *shell_c, t_icanon *icanon);

int 				ft_route_command(const char *command, char **args,
					int fd[2], char **line, t_config *shell_c, int pipefd[2]);

int					ft_update_env(t_config *shell_c);
int					ft_del_env(t_config *shell_c, char *str);
int					ft_add_env(t_config *shell_c, const char *str);

int					ft_update_shell(t_config *shell_c);


#endif
