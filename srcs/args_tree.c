/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 14:59:35 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/28 11:09:23 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_quotes(char quote, const char *str, int *i)
{
	int	bslash;

	bslash = 0;
	while (str[++(*i)] && (str[*i] != quote || bslash))
	{
		bslash = 0;
		if (str[*i] == '\\')
			bslash = 1;
	}
}

char	*ft_strinstr_quotes(const char *str, const char *sep)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			skip_quotes('\"', str, &i);
		if (str[i] == '\'')
			skip_quotes('\'', str, &i);
		if (ft_strchr(sep, str[i]) != NULL)
			return ((char *)&str[i]);
		if (str[i])
			i++;
	}
	return (NULL);
}

int	ft_in_str_where(char *str, char c, int last)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			if (last)
				while (str[i] == c)
					i++;
			return (i);
		}
		i++;
	}
	return (0);
}

int	loop_cmd(t_config *shell_c, char *str, t_cmd **cmd)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	while (str[i])
	{
		ft_cmdadd_back(cmd, ft_new_cmd(shell_c, &str[i],
				&error));
		if (error)
		{
			free_all_cmd(*cmd);
			return (error);
		}
		if (*cmd == NULL)
		{
			free_all_cmd(*cmd);
			return (0);
		}
		if (str[i] == '\0')
			break ;
		ft_skip_cmd(str, &i);
		ft_skip_spaces(str, &i);
	}
	return (-1);
}

int	ft_init_args_tree(t_config *shell_c, char *const buffer)
{
	int		i;
	int		ret;
	char	*str;
	t_cmd	*cmd;

	i = 0;
	cmd = NULL;
	str = buffer;
	ret = loop_cmd(shell_c, str, &cmd);
	if (ret != -1)
		return (ret);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	i = ft_recursiv_command(cmd, shell_c, STDIN_FILENO, dup(STDOUT_FILENO));
	return (i);
}
