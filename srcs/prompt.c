/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:09:52 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/12 12:42:06 by vfurmane         ###   ########.fr       */
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

int			ft_init_args_tree(char *const buffer, char **environement, int pipefd[2])
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
			return (0);
		if (str[i] == '\0')
			break ;
		while (str[i] && ft_strchr(";|<>", str[i]) == NULL)
			i++;
		while (str[i] && ft_strchr(";|<>", str[i]) != NULL)
			i++;
	}
	if (cmd == NULL)
		return (0);
	return (ft_handle_command(cmd, environement, pipefd));
}

int			ft_prompt(int *quit, char **environement, int pipefd[2])
{
	int		ret;
	char	buffer[ARG_MAX + 1];

	(void)quit; /* ===== DELETE ===== */
	write(1, "$ ", 2);
	ret = read(0, buffer, ARG_MAX);
	if (ret < 0)
		return (-1);
	else if (ret == 0)
	{
		write(1, "exit\n", 5);
		exit(S_SIGQUITSH);
		return (0);
	}
	buffer[ret - 1] = '\0';
	return (ft_init_args_tree(buffer, environement, pipefd));
}
