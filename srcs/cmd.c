/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 18:42:16 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/14 11:37:08 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_recursiv_command(t_cmd *cmd, t_config *shell_c, int pipe_in, int std_out)
{
	int		id;
	int		ret;
	int		status;
	char	**args;

	if (!cmd)
	{
		close(pipe_in);
		close(std_out);
		return (0);
	}
	signal(SIGQUIT, SIG_DFL);
	id = fork();
	if (id)
	{
		if (cmd->file)
			close(cmd->file);
		close(pipe_in);
		close(std_out);
		close(STDOUT_FILENO);
		wait(&status);
		return (WEXITSTATUS(status));
	}
	args = ft_split_cmd(shell_c, cmd->str/*, cmd->fd*/);
	if (args == NULL)
		return (-1);
	if (args[0] != NULL)
	{

		if (cmd->separator == PIPE) // case where there is > and pipe don't work
		{
			pipe(cmd->fd);
			if (cmd->from_to == BRACKET_TO)
			{
				dup2(cmd->file, STDOUT_FILENO);
				close(cmd->file);
				close(cmd->fd[1]);
			}
			else
			{
				dup2(cmd->fd[1], STDOUT_FILENO);
				close(cmd->fd[1]);
			}
		}
		else
		{
			if (cmd->from_to == BRACKET_TO)
			{
				//close(std_out);
				//std_out = cmd->file;
				dup2(cmd->file, STDOUT_FILENO);
				close(cmd->file);
			}
			else
				dup2(std_out, STDOUT_FILENO);
			//close(std_out);
		}
		if (cmd->from_to == BRACKET_FROM)
		{
			dup2(cmd->file, STDIN_FILENO);
			close(cmd->file);
			//close(pipe_in); //maybe usefull
		}
		else
		{
			dup2(pipe_in, STDIN_FILENO);
			if (pipe_in != STDIN_FILENO)
				close(pipe_in);
		}
		ret = ft_route_command(args[0], &args[1], cmd->fd, args, shell_c, cmd);
		close(STDIN_FILENO);
		ft_recursiv_command(cmd->next, shell_c, cmd->fd[0], std_out);
		exit(ret);
	}
	return (0);
}
