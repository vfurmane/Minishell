/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 18:42:16 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/20 17:28:48 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// All static here...

void ft_unterminated_quote(int fd)
{
	write(fd, "minishell: unterminated quote\n", 31);
}

int ft_arglen(const char *str, char chr, char **environment)
{
	int i;
	int j;
	char quote;

	i = 0;
	j = 0;
	quote = '\0';
	while (str[i] && (str[i] != chr || quote != '\0'))
	{
		if (quote != '\0' && str[i] == quote)
			quote = '\0' * i++;
		else if (quote == '\0' && (str[i] == '"' || str[i] == '\''))
			quote = str[i++];
		else
		{
			if (str[i++] == '$' && quote != '\'')
				j += ft_strlen(ft_exportenv(&str[i], &i, environment));
			else
				j++;
		}
	}
	return (j);
}

char *ft_parse_arg(const char *str, char chr, int fd[2], char **environment)
{
	int i;
	int j;
	char quote;
	char *new_str;

	i = 0;
	j = 0;
	quote = '\0';
	if (!(new_str = malloc(sizeof(*new_str) * (ft_arglen(str, chr, environment) + 1))))
		return (NULL);
	while (str[i] && (str[i] != chr || quote != '\0'))
		if (quote != '\0' && str[i] == quote)
			quote = '\0' * i++;
		else if (quote == '\0' && (str[i] == '"' || str[i] == '\''))
			quote = str[i++];
		else
		{
			if (str[i++] == '$' && quote != '\'')
				j += ft_strcpy(&new_str[j], ft_exportenv(&str[i], &i, environment));
			else
				new_str[j++] = str[i - 1];
		}
	new_str[j] = '\0';
	if (quote != '\0')
	{
		ft_unterminated_quote(fd[1]);
		return (NULL);
	}
	return (new_str);
}

int ft_count_words(const char *str)
{
	int i;
	int j;
	char quote;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '\0')
			break;
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

void ft_print_command(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		printf("|%s|", arr[i]);
		i++;
	}
	printf("\n");
}

char **ft_split_cmd_args(const char *str, int fd[2], char **environment)
{
	int i;
	int j;
	char quote;
	char **arr;

	i = 0;
	j = 0;
	arr = malloc(sizeof(*arr) * (ft_count_words(str) + 1)); //need protec
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '\0')
			break;
		else
			arr[j] = ft_parse_arg(&str[i], ' ', fd, environment);
		if (arr[j++] == NULL) /* leaks possible */
			return (NULL);
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
	arr[j] = NULL;
	//ft_print_command(arr);
	return (arr);
}

int ft_handle_command(t_cmd *cmd, t_config *shell_c, int pipefd[2])
{
	char	**args;
	t_cmd	*cmdi;

	cmdi = cmd;
	// loop
	while (cmdi)
	{
		cmdi->fd[0] = 0;
		cmdi->fd[1] = cmd->fd[1];
		if (cmdi->separator != EOCMD)
			pipe(cmdi->fd);
		args = ft_split_cmd_args(cmdi->str, cmdi->fd, shell_c->envp);
		if (args == NULL)
			return (-1);
		if (args[0] != NULL)
			if (ft_route_command(args[0], &args[1], cmdi->fd, args, shell_c, pipefd) == -42) //can't appening let's review that
				return (-1);
		cmdi = cmdi->next;
	}
	return (0);
}
