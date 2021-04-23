/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   router.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 11:52:44 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/23 18:15:17 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_command_not_found(const char *command, int fd)
{
	write(fd, "minishell: ", 12);
	write(fd, command, ft_strlen(command));
	write(fd, ": command not found\n", 21);
}

void ft_kill_child(int id)
{
	kill(id, SIGINT);
}

int ft_route_command(const char *command, char **args, int fd[2], char **line, t_config *shell_c, t_cmd *cmd)
{
	int ret;
	int id;

(void)cmd;
	ret = 0;

	// id = fork();
	// if (id)
	// {
	// 	if (cmd->separator == 42)
	// 	{
	// 		close(cmd->fd[0]);
	// 		dup2(cmd->fd[1], STDOUT_FILENO);
	// 		close(cmd->fd[1]);
	// 	}
	// 	//program here
	// 	wait(&ret);
	// 	return (ret);
	// }
	// if (cmd->separator == 42)
	// {
	// 	close(cmd->fd[1]);
	// 	dup2(STDIN_FILENO, cmd->fd[0]);
	// 	close(cmd->fd[0]);
	// }
	// //next program here

	if (ft_strcmp("echo", command) == 0)
		ret = ft_echo(args, STDOUT_FILENO);
	else if (ft_strcmp("cd", command) == 0)
		ret = ft_cd(args, STDOUT_FILENO, shell_c->envp, shell_c);
	else if (ft_strcmp("pwd", command) == 0)
		ret = ft_pwd(args, STDOUT_FILENO);
	else if (ft_strcmp("export", command) == 0)
		ret = ft_export(args, STDOUT_FILENO, shell_c, 1);
	else if (ft_strcmp("unset", command) == 0)
		ret = ft_unset(args, shell_c);
	else if (ft_strcmp("env", command) == 0)
		ret = ft_env(args, STDOUT_FILENO, shell_c->envp);
	else if (ft_strcmp("exit", command) == 0)
		ret = ft_exit(args, STDOUT_FILENO, shell_c);
	else if (ft_strchr(command, '/'))
	{
		id = fork();
		if (id)
			wait(0);
		else
		ft_execve(line[0], line, NULL); //cas ou existe pas
	}
	else
	{
		id = fork();
		if (id)
			wait(0);
		else
		 if (!ft_exec(line, shell_c->envp))
		{
			ft_command_not_found(command, STDOUT_FILENO);
			exit(0);
		}
	}
	return (ret);
}
