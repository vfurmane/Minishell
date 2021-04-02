/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 10:33:11 by earnaud           #+#    #+#             */
/*   Updated: 2021/04/02 15:29:58 by earnaud          ###   ########.fr       */
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

int ft_exec(char **command)
{
	char *pathfile;
	add_slash(command);
	pathfile = check_in(command[0]);
	if (pathfile)
	{
		free(command[0]);
		command[0] = pathfile;
	execve(command[0], command, NULL);
	//does execve free param?
	}
	return (0);
}