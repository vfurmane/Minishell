/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_states.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:22:13 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/27 10:20:27 by vfurmane         ###   ########.fr       */
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

int	ft_set_backslash(t_cmd_arg *arg, char chr, int *i)
{
	if (arg->backslash == 0 && chr == '\\' && arg->quote == '\0')
	{
		arg->backslash = 1;
		(*i)++;
		return (1);
	}
	else
		return (0);
}
