/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 18:42:16 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/23 18:12:46 by earnaud          ###   ########.fr       */
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
	int		i;
	int		j;
	char	quote;
	char	*new_str;

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

int ft_recursiv_command(t_cmd *cmd, t_config *shell_c, int pipe_in, int std_out)
{
	int id;
	char **args;

	if (!cmd)
	{
		close(pipe_in);
		close(std_out);
		return (0);
	}
	id = fork();
	if (id)
	{
		close(pipe_in);
		close(std_out); //?
		wait(&id);
		return (id);
	}
	args = ft_split_cmd_args(cmd->str, cmd->fd, shell_c->envp);
	if (args == NULL)
		return (-1);
	if (args[0] != NULL)
	{
		if (cmd->separator == PIPE)
		{
			pipe(cmd->fd);
			dup2(cmd->fd[1], STDOUT_FILENO);
			close(cmd->fd[1]); //close the pipe?
		}
		else
		{
			dup2(std_out, STDOUT_FILENO);
			close(std_out);
		}
		dup2(pipe_in, STDIN_FILENO);
		close(pipe_in);		 //close the pipe?
		ft_route_command(args[0], &args[1], cmd->fd, args, shell_c, cmd);
		//write(STDOUT_FILENO, "okay\n", 6);
		return (ft_recursiv_command(cmd->next, shell_c, cmd->fd[0], std_out));
	}
	
	return (0);
}
int ft_handle_command(t_cmd *cmd, t_config *shell_c, int pipefd[2])
{
	char	**args;
	t_cmd	*cmdi;
	//int id;

	(void)pipefd;

	cmdi = cmd;
	// loop
	while (cmdi)
	{
		args = ft_split_cmd_args(cmdi->str, cmdi->fd, shell_c->envp);
		if (args == NULL)
			return (-1);
		if (args[0] != NULL)
		{
			// if (cmdi->separator == 42)
			// {
			// 	pipe(cmdi->fd);
			// }
			ft_route_command(args[0], &args[1], cmdi->fd, args, shell_c, cmdi);
			cmdi = cmdi->next;
		}
	}
	return (0);
}
