/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_command2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 15:31:10 by earnaud           #+#    #+#             */
/*   Updated: 2021/05/28 15:32:29 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_fix_openfiles_loop(t_config *shell_c, char *const buffer,
								t_cmd *cmd, int *i)
{
	while (buffer[*i] && !ft_strchr("|;", buffer[*i]))
	{
		if (skip_quotes(buffer, i))
		{
			free(buffer);
			free_shell(shell_c);
			free_all_cmd(cmd);
			exit(-1);
		}
		if (ft_strchr("<>", buffer[*i]))
		{
			if (pars_files(buffer, shell_c, cmd, i) == -1)
				return (0);
		}
		else if (buffer[*i])
			(*i)++;
	}
	return (1);
}

char	*ft_fix_openfiles(t_config *shell_c, char *const buffer,
		t_cmd *cmd, int *error)
{
	int	i;

	if (!buffer)
		return (0);
	i = 0;
	if (!ft_fix_openfiles_loop(shell_c, buffer, cmd, &i))
	{
		*error = 1;
		return (0);
	}
	if (cmd->file_from || cmd->file_to)
		return (buffer_fix(buffer));
	return (NULL);
}
