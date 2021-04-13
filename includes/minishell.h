/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:20:33 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/13 10:15:59 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <linux/limits.h>
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
# include "utils.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# ifndef S_SIGQUITSH
#  define S_SIGQUITSH 255
# endif

# ifndef S_SIGUPENV
#  define S_SIGUPENV 254
# endif

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
	struct s_cmd	*next;
	char			*str;
	t_separator		separator;
	int				fd[2];
}					t_cmd;

int					ft_handle_command(t_cmd *cmd, char **environement, int pipefd[2]);
char				**ft_split_cmd_args(const char *str, int fd[2]);
int					ft_route_command(const char *command, char **args, int fd[2], char **line, char **environement, int pipefd[2]);
char				*ft_getenv(const char *str, int *str_i);
int					ft_prompt(int *quit, char **environement, int pipefd[2]);
void				ft_update_env(int pipefd[2], char ***environement);
void				copy_env(char **new_env, char **args, char **environement, int pipefd[2]);

size_t ft_strlen(const char *str);
size_t ft_strstrlen(char **str);
char **ft_env_malloc(char **envp);
char *ft_strjoin(char const *s1, char const *s2);
size_t ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s);
size_t ft_strcpy(char *dest, const char *src);
void	*ft_memset(void *str, int c, size_t n);
void nothing();
int	ft_execve(const char *filename, char *const argv[], char *const envp[]);
int ft_exec(char **command, char **environement);
char **ft_split(char const *s, char c);

#endif
