/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 13:32:16 by earnaud           #+#    #+#             */
/*   Updated: 2021/05/11 09:56:07 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_parse_new_dir(t_config *shell_c, char **args, char **new_dir)
{
	if (args[0] == NULL || ft_strcmp("~", args[0]) == 0)
	{
		*new_dir = ft_getenv(shell_c->envp_list, "HOME");
		if (*new_dir == NULL)
			return (ft_stderr_message("cd: HOME not set", NULL, NULL, -1));
	}
	else if (ft_strcmp("-", args[0]) == 0)
	{
		*new_dir = ft_getenv(shell_c->envp_list, "OLDPWD");
		if (*new_dir == NULL)
			return (ft_stderr_message("cd: OLDPWD not set", NULL, NULL, -1));
	}
	else if (args[1] != NULL)
		return (ft_stderr_message("cd: too many arguments", NULL, NULL, -1));
	else
		*new_dir = args[0];
	return (0);
}

int			ft_cd(t_config *shell_c, char **args, int output_fd)
{
	int		ret;
	char	*new_dir;
	char	*new_pwd;
	char	*old_pwd;

	(void)output_fd; /* ===== DELETE ===== */
	ret = ft_parse_new_dir(shell_c, args, &new_dir);
	if (ret == -1)
		return (1);
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
