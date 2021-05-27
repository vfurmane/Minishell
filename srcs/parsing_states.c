/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_states.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:22:13 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/27 11:57:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	ft_set_quote(t_cmd_arg *arg, char chr)
{
	if (arg->quote != '\0' && arg->quote == chr)
		arg->quote = '\0';
	else if (arg->quote == '\0' && (chr == '"' || chr == '\''))
		arg->quote = chr;
	else
	{
		if (arg->str != NULL)
			arg->str[arg->i] = chr;
		arg->i++;
	}
	return (arg->quote);
}

int	ft_set_backslash(t_cmd_arg *arg, const char *cmd, int *i)
{
	if (!arg->backslash && cmd[*i] == '\\' && (arg->quote == '\0'
			|| (cmd[*i + 1] != '\0' && arg->quote == cmd[*i + 1])))
	{
		arg->backslash = 1;
		(*i)++;
		return (1);
	}
	else
		return (0);
}
