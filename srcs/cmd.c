/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 18:42:16 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/30 23:29:47 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int	ret;

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

int	first_setup(t_cmd *cmd, t_config *shell_c, int *pipe_fshell, int count[0])
{
	if (!cmd)
	{
		if (pipe_fshell[3])
			free_shell(shell_c);
		close(pipe_fshell[2]);
		return (0);
	}
	count[0] = fork();
	if (count[0] == -1)
		return (ft_stderr_message("could not fork: ", strerror(errno),
				  NULL, -1));
	else if (count[0] != CHILD_PROCESS)
		 return (main_process(cmd, shell_c, pipe_fshell));
	return (-42);
}

t_cmd	*set_next_value(t_cmd *cmd, int *pipe_fshell,
			int *count)
{
	t_cmd	*cmd_next;

	switch_case_dup(cmd, pipe_fshell[0], pipe_fshell[1]);
	free(cmd->str);
	cmd_next = cmd->next;
	count[3] = cmd->fd[0];
	free(cmd);
	return (cmd_next);
}

int	ft_recursiv_command(t_cmd *cmd, t_config *shell_c, int *pipe_fshell)
{
	int		count[4];
	char	**args;
	t_cmd	*cmd_next;
	int		ret;

	ret = first_setup(cmd, shell_c, pipe_fshell, count);
	if (ret != -42)
		return (ret);
	args = ft_split_cmd(shell_c, cmd->str);
	if (args == NULL)
		return (-1);
	if (args[0] != NULL)
	{
		cmd_next = set_next_value(cmd, pipe_fshell, count);
		count[2] = ft_route_command(shell_c, args, cmd_next);
		free_neo(args);
		pipe_fshell[0] = count[3];
		pipe_fshell[2] = 1;
		ft_recursiv_command(cmd_next, shell_c, pipe_fshell);
		exit (count[2]);
	}
	return (0);
}
