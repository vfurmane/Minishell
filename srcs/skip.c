/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 16:52:17 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/25 17:22:01 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_skip_spaces(const char *cmd, int *i)
{
	while (cmd[*i] == ' ')
		(*i)++;
	return ((char *)(&cmd[*i]));
}

char	*ft_skip_cmd_arg(const char *cmd, int *i)
{
	t_cmd_arg	arg;

	ft_bzero(&arg, sizeof(arg));
	while (cmd[*i] && (cmd[*i] != ' ' || arg.quote != '\0'))
	{
		if (!arg.backslash && cmd[*i] == '\\')
		{
			arg.backslash = cmd[(*i)++] == '\\';
			continue ;
		}
		if (arg.backslash)
			(*i)++;
		else if (cmd[*i] == '\'' || cmd[*i] == '"')
			arg.quote = ft_set_quote(&arg, cmd[(*i)++]);
		else
			(*i)++;
		arg.backslash = 0;
	}
	return ((char *)&cmd[*i]);
}
