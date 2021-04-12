/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 10:33:11 by earnaud           #+#    #+#             */
/*   Updated: 2021/04/12 12:31:18 by vfurmane         ###   ########.fr       */
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

char *check_in(char *program)
{
	char **path;
	char *pathfile;
	int i;
	struct stat stats;
	
	i = 0;
	path = ft_split(getenv("PATH"), ':');
	while (path[i])
	{
		pathfile = ft_strjoin(path[i], program);
		if (!stat(pathfile, &stats))
		{
			ft_free_neo(path);
			return (pathfile);
		}
		free(pathfile);
		i++;
		//return (path[i]);
	}
	ft_free_neo(path);
	return (0);
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
	{
		printf("minishell: %s: %s\n", filename, strerror(errno));
	}
	return (ret);
}

int ft_exec(char **command, char **environement)
{
	char	*pathfile;
	char	*slash_command;

	slash_command = ft_strjoin("/", command[0]);
	//add_slash(command);
	pathfile = check_in(slash_command);
	free(slash_command);
	if (pathfile)
	{
		ft_execve(pathfile, command, environement);
		//does execve free param ? No, we need to free in the main process
	}
	return (0);
}
