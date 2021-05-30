/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_util2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 23:28:01 by earnaud           #+#    #+#             */
/*   Updated: 2021/05/30 23:30:46 by earnaud          ###   ########.fr       */
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
