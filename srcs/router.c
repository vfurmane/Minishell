/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   router.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 11:52:44 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/01 12:34:51 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_command_not_found(const char *command)
{
	printf("minishell: %s: command not found\n", command);
}

int		ft_route_command(const char *command, char **args, int fd[2])
{
	int	ret;

	ret = 0;
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
		ret = ft_exit(args, fd[1]);
	else
		ft_command_not_found(command);
	return (ret);
}
