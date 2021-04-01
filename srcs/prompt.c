/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:09:52 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/01 14:16:34 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_separator	ft_set_separator(const char *str)
{
	if (str[0] == ';')
		return (EOCMD);
	else if (str[0] == '<')
		return (REDIR_LEFT);
	else if (str[0] == '>')
		if (str[1] == '>')
			return (REDIR_APPEND);
		else
			return (REDIR_RIGHT);
	else if (str[0] == '|')
		return (PIPE);
	else
		return (EOCMD);
}

t_cmd		*ft_new_cmd(char *const buffer)
{
	t_cmd	*cmd;
	char	*separator;

	cmd = malloc(sizeof(*cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->next = NULL;
	separator = ft_strinstr(buffer, ";|<>");
	if (separator == NULL)
		separator = &buffer[ft_strlen(buffer)];
	cmd->str = ft_strndup(buffer, separator - buffer);
	if (cmd->str == NULL)
		return (NULL);
	cmd->separator = ft_set_separator(separator);
	return (cmd);
}

int			ft_init_args_tree(char *const buffer)
{
	int		i;
	char	*str;
	t_cmd	*initial_cmd;
	t_cmd	*cmd;

	i = 0;
	initial_cmd = NULL;
	cmd = NULL;
	str = buffer;
	while (str[i])
	{
		cmd = ft_lstadd_back(&initial_cmd, ft_new_cmd(&str[i]));
		if (cmd == NULL)
			return (-1);
		while (str[i] && ft_strchr(";|<>", str[i]) == NULL)
			i++;
		while (str[i] && ft_strchr(";|<>", str[i]) != NULL)
			i++;
	}
	ft_handle_command(cmd);
	return (0);
}

int			ft_prompt(void)
{
	int		ret;
	char	buffer[ARG_MAX + 1];

	write(1, "$ ", 2);
	ret = read(0, buffer, ARG_MAX);
	if (ret <= 0)
		return (-1);
	buffer[ret - 1] = '\0';
	ft_init_args_tree(buffer);
	return (1);
}
