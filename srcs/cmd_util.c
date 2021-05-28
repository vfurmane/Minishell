/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 10:53:23 by earnaud           #+#    #+#             */
/*   Updated: 2021/05/28 11:09:21 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_separator	ft_set_separator(const char *str)
{
	if (str[0] == ';')
		return (EOCMD);
	else if (str[0] == '|')
		return (PIPE);
	else
		return (EOCMD);
}

t_cmd	*ft_cmdlast(t_cmd *cmd)
{
	if (!(cmd))
		return (0);
	while (cmd->next)
		cmd = cmd->next;
	return (cmd);
}

void	ft_cmdadd_back(t_cmd **acmd, t_cmd *new)
{
	if (!(*acmd))
	{
		*acmd = new;
		return ;
	}
	ft_cmdlast(*acmd)->next = new;
}

char	*ft_skip_cmd(const char *cmd, int *i)
{
	int			j;
	t_cmd_arg	arg;

	ft_bzero(&arg, sizeof(arg));
	j = 0;
	while (cmd[*i] && ((cmd[*i] != ';' && cmd[*i] != '|') || arg.quote != '\0'))
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
	if (cmd[*i] == ';' || cmd[*i] == '|')
		(*i)++;
	return ((char *)&cmd[*i]);
}

t_cmd	*ft_new_cmd(t_config *shell_c, char *const buffer, int *error)
{
	t_cmd	*cmd;
	char	*separator;
	char	*buffer_fix;

	cmd = ft_calloc(1, sizeof(*cmd));
	if (cmd == NULL)
		return (NULL);
	buffer_fix = ft_fix_openfiles(shell_c, buffer, cmd, error);
	separator = ft_strinstr_quotes(buffer, ";|");
	if (separator == NULL)
		separator = &buffer[ft_strlen(buffer)];
	if (buffer_fix)
		cmd->str = buffer_fix;
	else if (!*error)
		cmd->str = ft_strndup(buffer, separator - buffer);
	else
		return (NULL);
	cmd->separator = ft_set_separator(separator);
	return (cmd);
}
