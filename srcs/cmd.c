/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 18:42:16 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/24 17:43:15 by earnaud          ###   ########.fr       */
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
		close(std_out);
		return (0);
	}
	id = fork();
	if (id == -1)
		return (ft_stderr_message("could not fork: ", strerror(errno),
								  NULL, -1));
	else if (id != CHILD_PROCESS)
	{
		close(cmd->file_to);
		close(cmd->file_from);
		close(pipe_in);
		close(std_out);
		close(STDOUT_FILENO);
		free_all_cmd(cmd);
		wait(&status);
		return (WEXITSTATUS(status));
	}
	args = ft_split_cmd(shell_c, cmd->str);
	if (args == NULL)
		return (-1);
	if (args[0] != NULL)
	{
		if (cmd->separator == PIPE)
		{
			pipe(cmd->fd);
			if (cmd->from_to == BRACKET_TO)
			{
				dup2(cmd->file_to, STDOUT_FILENO);
				close(cmd->file_to);
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
			if (cmd->file_to)
			{
				dup2(cmd->file_to, STDOUT_FILENO);
				close(cmd->file_to);
			}
			else
				dup2(std_out, STDOUT_FILENO);
		}
		if (cmd->file_from)
		{
			dup2(cmd->file_from, STDIN_FILENO);
			close(cmd->file_from);
			//close(pipe_in); //maybe usefull
		}
		else
		{
			dup2(pipe_in, STDIN_FILENO);
			if (pipe_in != STDIN_FILENO)
				close(pipe_in);
		}
		ret = ft_route_command(args[0], &args[1], args, shell_c);
		free_neo(args);
		if (ret != 127)
			ft_recursiv_command(cmd->next, shell_c, cmd->fd[0], std_out);
		free_all_cmd(cmd);
		free_shell(shell_c);
		exit (ret);
	}
	return (0);
}
