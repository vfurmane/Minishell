/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 18:42:16 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/28 17:33:27 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	where_to_cut(char *const buffer)
{
	int	i;

	i = 0;
	if (!buffer)
		return (0);
	while (buffer[i])
	{
		if (ft_strchr(";| ", buffer[i]))
			return (i);
		i++;
	}
	return (i);
}

void	switch_case_pipe_to(t_cmd *cmd, int std_out)
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
}

void	switch_case_dup(t_cmd *cmd, int pipe_in, int std_out)
{
	switch_case_pipe_to(cmd, std_out);
	if (cmd->file_from)
	{
		dup2(cmd->file_from, STDIN_FILENO);
		close(cmd->file_from);
	}
	else
	{
		dup2(pipe_in, STDIN_FILENO);
		if (pipe_in != STDIN_FILENO)
			close(pipe_in);
	}
}

int	main_process(t_cmd *cmd, t_config *shell_c, int *pipe_fshell)
{
	int ret;
	switch_case_dup(cmd, pipe_fshell[0], pipe_fshell[1]);
	close(cmd->file_to);
	close(cmd->file_from);
	close(pipe_fshell[0]);
	close(pipe_fshell[1]);
	close(STDOUT_FILENO);
	free_all_cmd(cmd);
	if (pipe_fshell[2])
		free_shell(shell_c);
	wait(&ret);
	return (WEXITSTATUS(ret));
}

int ft_recursiv_command(t_cmd *cmd, t_config *shell_c, int *pipe_fshell)
{
	int		count[4];
	char	**args;
	t_cmd	*cmd_next;

	if (!cmd)
	{
		close(pipe_fshell[2]);
		return (0);
	}
	count[0] = fork();
	if (count[0] == -1)
		return (ft_stderr_message("could not fork: ", strerror(errno),
								  NULL, -1));
	else if (count[0] != CHILD_PROCESS)
		return (main_process(cmd, shell_c, pipe_fshell));
	args = ft_split_cmd(shell_c, cmd->str);
	if (args == NULL)
		return (-1);
	if (args[0] != NULL)
	{
		switch_case_dup(cmd, pipe_fshell[0], pipe_fshell[1]);
		free(cmd->str);
		cmd_next = cmd->next;
		count[3] = cmd->fd[0];
		free(cmd);
		count[2] = ft_route_command(shell_c, args);
		free_neo(args);
		pipe_fshell[0] = count[3];
		pipe_fshell[2] = 1;
		ft_recursiv_command(cmd_next, shell_c, pipe_fshell);
		exit (count[2]);
	}
	return (0);
}
