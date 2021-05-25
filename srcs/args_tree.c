/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 14:59:35 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/25 15:03:40 by vfurmane         ###   ########.fr       */
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

char	*ft_strinstr_quotes(const char *str, const char *sep)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			while (str[++i] && str[i] != '\"')
				i = i + 0;
		if (str[i] == '\'')
			while (str[++i] && str[i] != '\'')
				i = i + 0;
		if (ft_strchr(sep, str[i]) != NULL)
			return ((char *)&str[i]);
		if (str[i])
			i++;
	}
	return (NULL);
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

static char	ft_set_quote(t_cmd_arg *arg, char chr)
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

static char	*ft_skip_spaces(const char *cmd, int *i)
{
	while (cmd[*i] == ' ')
		(*i)++;
	return ((char *)(&cmd[*i]));
}

static char	*ft_skip_cmd(const char *cmd, int *i)
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
	(*i)++;
	return ((char *)&cmd[*i]);
}

int	ft_init_args_tree(t_config *shell_c, char *const buffer)
{
	int		i;
	char	*str;
	t_cmd	*cmd;
	int		bracket;
	int		errorfile;

	i = 0;
	errorfile = 0;
	bracket = 0;
	cmd = NULL;
	str = buffer;
	while (str[i])
	{
		ft_cmdadd_back(&cmd, ft_new_cmd(shell_c, &str[i], &errorfile));
		if (errorfile)
		{
			free_all_cmd(cmd);
			return (errorfile);
		}
		if (cmd == NULL)
		{
			free_all_cmd(cmd);
			return (0);
		}
		if (str[i] == '\0')
			break ;
		ft_skip_cmd(str, &i);
		ft_skip_spaces(str, &i);
	}
	i = ft_recursiv_command(cmd, shell_c, STDIN_FILENO, dup(STDOUT_FILENO));
	return (i);
}
