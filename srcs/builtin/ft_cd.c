/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 13:32:16 by earnaud           #+#    #+#             */
/*   Updated: 2021/04/20 12:19:05 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int flag(char *str)
{
	if (str)
		if (ft_strchr(str, '-'))
			return (1);
	return (0);
}

static int write_cd(int fd, char *str, t_config *shell_c)
{
	char *big_str[2];

	write(fd, CD_CHANGE, 3);
	write(fd, "\x1F", 1);
	write(fd, str, ft_strlen(str));
	write(fd, "\x1E", 1);
	chdir(str);
	big_str[0] = ft_strjoin("PWD=", getcwd(NULL, 0));
	big_str[1] = 0;
	ft_export(big_str, fd, shell_c, 0);
	free(big_str[0]);
	return (1);
}

void set_oldpwd(int fd, char *pwd, t_config *shell_c)
{
	char *big_str[2];

	big_str[0] = ft_strjoin("OLDPWD=", pwd);
	big_str[1] = 0;
	ft_export(big_str, fd, shell_c, 0);
	free(big_str[0]);
}

int ft_cd(char **str, int fd, char **envp, t_config *shell_c)
{
	fd = 0;
	if (str[1])
		return (write(fd, "cd : too much arguments\n", 25));
	set_oldpwd(shell_c->fd[1], ft_getenv(envp, "PWD"), shell_c);
	if (flag(*str))
		return (write_cd(shell_c->fd[1], ft_getenv(envp, "OLDPWD"), shell_c));
	if (!*str || **str == '~')
		return (write_cd(shell_c->fd[1], ft_getenv(envp, "HOME"), shell_c));
	return (write_cd(shell_c->fd[1], *str, shell_c));
}
