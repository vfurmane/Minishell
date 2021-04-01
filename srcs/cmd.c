/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 18:42:16 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/01 11:41:46 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// All static here...

char	*ft_add_arg_to_arr(const char *str, char chr)
{
	int		i;
	char	quote;
	char	*new_str;

	i = 0;
	quote = '\0';
	while (str[i] && (str[i] != chr && quote == '\0'))
	{
		if (quote != '\0' && str[i] == quote)
			quote = '\0';
		else if (quote == '\0' && (str[i] == '"' || str[i] == '\''))
			quote = str[i];
		if (str[i] == '\0' && quote != '\0')
			return (NULL);
		i++;
	}
	if (!(new_str = malloc(sizeof(*new_str) * (i + 1))))
		return (NULL);
	new_str = ft_memcpy(new_str, str, sizeof(*new_str) * i);
	new_str[i] = '\0';
	return (new_str);
}

int	ft_count_words(const char *str)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '\0')
			break ;
		else
			j++;
		quote = '\0';
		while (str[i] && (quote != '\0' || str[i] != ' '))
		{
			if (quote != '\0' && str[i] == quote)
				quote = '\0';
			else if (quote == '\0' && (str[i] == '"' || str[i] == '\''))
				quote = str[i];
			if (str[i] == '\0' && quote != '\0')
				return (-1);
			i++;
		}
	}
	return (j);
}

char	**ft_split_cmd_args(const char *str)
{
	int		i;
	int		j;
	char	quote;
	char	**arr;

	i = 0;
	j = 0;
	arr = malloc(sizeof(*arr) * (ft_count_words(str) + 1));
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '\0')
			break ;
		else
			arr[j++] = ft_add_arg_to_arr(&str[i], ' ');
		quote = '\0';
		while (str[i] && (quote != '\0' || str[i] != ' '))
		{
			if (quote != '\0' && str[i] == quote)
				quote = '\0';
			else if (quote == '\0' && (str[i] == '"' || str[i] == '\''))
				quote = str[i];
			if (str[i] == '\0' && quote != '\0')
				return (NULL);
			i++;
		}
	}
	return (arr);
}

int		ft_handle_command(t_cmd *cmd)
{
	char	**args;
	t_cmd	*cmdi;

	cmdi = cmd;
	pipe(cmdi->fd);
	args = ft_split_cmd_args(cmdi->str);
	return (0);
}
