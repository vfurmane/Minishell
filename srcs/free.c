/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 14:56:49 by earnaud           #+#    #+#             */
/*   Updated: 2021/05/30 23:02:23 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_all_cmd(t_cmd *cmd)
{
	t_cmd	*temp;

	while (cmd)
	{
		temp = cmd->next;
		free(cmd->str);
		free(cmd);
		cmd = temp;
	}
	return (0);
}

void	free_neo(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

void	free_neo_content(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
}

void	free_neocont_neo_shell(char **args, char **line, t_config *shell_c)
{
	free_neo_content(args);
	free_neo(line);
	free_shell(shell_c);
}

void	free_shell(t_config *shell_c)
{
	void		*temp;
	int			i;

	i = 0;
	free_neo(shell_c->envp);
	while (shell_c->envp_list)
	{
		temp = shell_c->envp_list->next;
		free(shell_c->envp_list->value);
		free(shell_c->envp_list->key);
		free(shell_c->envp_list);
		shell_c->envp_list = temp;
	}
	close(shell_c->fd[0]);
	close(shell_c->fd[1]);
	while (shell_c->history)
	{
		temp = shell_c->history->next;
		free(shell_c->history->content);
		free(shell_c->history);
		shell_c->history = temp;
	}
}
