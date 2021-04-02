/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   router.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 11:52:44 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/02 15:30:20 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_command_not_found(const char *command, int fd)
{
	write(fd, "minishell: ", 12);
	write(fd, command, ft_strlen(command));
	write(fd, ": command not found\n", 21);
}

int ft_route_command(const char *command, char **args, int fd[2], char **line)
{
	int ret;
	int id;

	id = fork();
	ret = 0;
	
	//can't use exit function because of the redirection of sigint, need to stop the program when receive -42

	if (id)
	{
		signal(SIGINT, nothing);
		wait(NULL);
		return (ret);
	}
	if (ft_strcmp("echo", command) == 0)
		ret = ft_echo(args, fd[1]);
	else if (ft_strcmp("cd", command) == 0)
		ret = ft_cd(args, fd[1]);
	else if (ft_strcmp("pwd", command) == 0)
		ret = ft_pwd(args, fd[1]);
	else if (ft_strcmp("export", command) == 0)
		ret = ft_export(args, fd[1]);
	else if (ft_strcmp("unset", command) == 0)
		ret = ft_unset(args, fd[1]);
	else if (ft_strcmp("env", command) == 0)
		ret = ft_env(args, fd[1]);
	else if (ft_strcmp("exit", command) == 0)
		return (-42);
	else
	{
		if (!ft_exec(line))
			ft_command_not_found(command, fd[1]);
	}
	return (ret);
}
