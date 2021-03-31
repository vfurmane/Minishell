/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:20:33 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/01 11:30:29 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <linux/limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <sys/wait.h>
# include <term.h>
# include <ncurses.h>
# include <termios.h>
# include "builtin.h"
# include "utils.h"

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

int					ft_handle_command(t_cmd *cmd);
int					ft_prompt(void);

size_t ft_strlen(const char *str);
char *ft_strjoin(char const *s1, char const *s2);
size_t ft_strlcpy(char *dest, const char *src, size_t size);
void nothing();

#endif
