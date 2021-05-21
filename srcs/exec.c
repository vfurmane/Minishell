/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 10:33:11 by earnaud           #+#    #+#             */
/*   Updated: 2021/05/21 12:18:55 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		**ft_free_neo(char **neo)
{
	size_t i;

	i = 0;
	if (neo)
	{
		while (neo[i])
			free(neo[i++]);
		free(neo);
	}
	return (0);
}

char *ft_get_executable_path(t_config *shell_c, char *program)
{
	char		**path;
	char		*pathfile;
	int			i;
	struct stat	file_stat;
	
	i = 0;
	path = ft_split(ft_getenv(shell_c->envp_list, "PATH"), ':');
	while (path[i])
	{
		pathfile = ft_strjoin(path[i], program);
		if (!stat(pathfile, &file_stat))
		{
			ft_free_neo(path);
			if (file_stat.st_mode & 040000)
				exit(ft_stderr_message(pathfile, ": Is a directory", NULL, 126));
			return (pathfile);
		}
		free(pathfile);
		i++;
	}
	ft_free_neo(path);
	return (NULL);
}

void add_slash(char **str)
{
	char *prog;
	prog = malloc(sizeof(char) * (ft_strlen(*str) + 2));
	if (!prog)
		return ;
	prog[0] = '/';
	ft_strlcpy(prog + 1, *str, ft_strlen(*str) + 1);
	free(*str);
	*str = prog;
}

int	ft_execve(const char *filename, char *const argv[], char *const envp[])
{
	int	ret;

	ret = execve(filename, argv, envp);
	if (ret == -1)
		ft_stderr_message(filename, ": ", strerror(errno), -1);
	return (ret);
}

int ft_exec(t_config *shell_c, char **command)
{
	char	*pathfile;
	char	*slash_command;

	slash_command = ft_strjoin("/", command[0]);
	pathfile = ft_get_executable_path(shell_c, slash_command);
	free(slash_command);
	if (pathfile)
		ft_execve(pathfile, command, shell_c->envp);
	return (0);
}
