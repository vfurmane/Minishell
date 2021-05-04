/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 13:32:16 by earnaud           #+#    #+#             */
/*   Updated: 2021/05/04 10:31:38 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_cd(char **str, int fd, t_config *shell_c)
{
	char	*new_dir;
	char	*new_pwd;
	char	*old_pwd;

	(void)fd; /* ===== DELETE ===== */
	if (str[0] == NULL || ft_strcmp("~", str[0]) == 0)
	{
		new_dir = getenv("HOME");
		if (new_dir == NULL)
			return (ft_stderr_message("cd: HOME not set", NULL, NULL, 1));
	}
	else if (ft_strcmp("-", str[0]) == 0)
	{
		new_dir = getenv("OLDPWD");
		if (new_dir == NULL)
			return (ft_stderr_message("cd: OLDPWD not set", NULL, NULL, 1));
	}
	else if (str[1] != NULL)
		return (ft_stderr_message("cd: too many arguments", NULL, NULL, 1));
	else
		new_dir = str[0];
	old_pwd = getcwd(NULL, 0);
	if (old_pwd == NULL)
		return (ft_stderr_message("cd: ", strerror(errno), NULL, 1));
	if (chdir(new_dir) == -1)
		return (ft_stderr_message("cd: ", strerror(errno), NULL, 1));
	new_pwd = getcwd(NULL, 0);
	ft_write_pipe(ADD_ENV, "PWD=", new_pwd, shell_c->fd[1]);
	ft_write_pipe(ADD_ENV, "OLDPWD=", old_pwd, shell_c->fd[1]);
	ft_write_pipe(CD_CHANGE, new_dir, NULL, shell_c->fd[1]);
	free(new_pwd);
	free(old_pwd);
	return (0);
}
