/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 14:34:59 by earnaud           #+#    #+#             */
/*   Updated: 2021/05/30 22:36:51 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_dquote(const char *str, int *i, int *bslash)
{
	*bslash = 0;
	if (str[*i] == '\\')
	{
		*bslash = 1;
		(*i)++;
	}
	if (str[*i] == '"' && !(*bslash))
	{
		*bslash = 0;
		(*i)++;
		while (str[*i] != '"')
		{
			if (str[*i] == '\\')
			{
				*bslash = 1;
				(*i)++;
			}
			if (!str[*i] && !(*bslash))
				return (ft_stderr_message("Error: ", "unterminated quote",
						NULL, -1));
			(*i)++;
		}
	}
	return (0);
}

int	skip_quotes(const char *str, int *i)
{
	int	bslash;

	if (skip_dquote(str, i, &bslash) == -1)
		return (-1);
	if (str[*i] == '\'' && !bslash)
	{
		bslash = 0;
		(*i)++;
		while (str[*i] != '\'')
		{
			if (str[*i] == '\\')
			{
				bslash = 1;
				(*i)++;
			}
			if (!str[*i] && !bslash)
				return (ft_stderr_message("Error: ", "unterminated quote",
						NULL, -1));
			(*i)++;
		}
	}
	return (0);
}

int	buffer_fix_loop(char *const buffer, char *str, int *count)
{
	while (buffer[count[0]] && !ft_strchr(";|", buffer[count[0]]))
	{
		count[2] = count[0];
		if (skip_quotes(buffer, count + 2) == -1)
			return (0);
		while (count[0] < count[2])
			str[count[1]++] = buffer[count[0]++];
		if (ft_strchr("<>", buffer[count[0]]))
		{
			while (ft_strchr(" <>", buffer[count[0]]))
				count[0]++;
			if (skip_quotes(buffer, count) == -1)
				return (0);
			while (buffer[count[0]] && !ft_strchr(" <>|;", buffer[count[0]]))
				count[0]++;
		}
		if (!ft_strchr(";|", buffer[count[0]]))
			str[count[1]++] = buffer[count[0]++];
	}
	return (1);
}

char	*buffer_fix(char *const buffer)
{
	char	*str;
	int		count[3];

	count[0] = 0;
	count[1] = 0;
	str = malloc(sizeof(char) * ft_strlen(buffer));
	if (!str)
		return (NULL);
	if (!buffer_fix_loop(buffer, str, count))
		return (NULL);
	str[count[1]] = 0;
	return (str);
}
