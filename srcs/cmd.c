/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 18:42:16 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/04 15:42:56 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// All static here...

void ft_unterminated_quote(int fd)
{
	write(fd, "minishell: unterminated quote\n", 31);
}

int ft_arglen(t_config *shell_c, const char *str, char chr)
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
				j += ft_strlen(ft_replace_with_env(shell_c, &str[i], &i));
			else
				j++;
		}
	}
	return (j);
}

char *ft_parse_arg(t_config *shell_c, const char *str, char chr, int fd[2])
{
	int		i;
	int		j;
	char	quote;
	char	*new_str;

	i = 0;
	j = 0;
	quote = '\0';
	if (!(new_str = malloc(sizeof(*new_str) * (ft_arglen(shell_c, str, chr) + 1))))
		return (NULL);
	while (str[i] && (str[i] != chr || quote != '\0'))
		if (quote != '\0' && str[i] == quote)
			quote = '\0' * i++;
		else if (quote == '\0' && (str[i] == '"' || str[i] == '\''))
			quote = str[i++];
		else
		{
			if (str[i++] == '$' && quote != '\'')
				j += ft_strcpy(&new_str[j], ft_replace_with_env(shell_c, &str[i], &i));
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

char **ft_split_cmd_args(t_config *shell_c, const char *str, int fd[2])
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
			arr[j] = ft_parse_arg(shell_c, &str[i], ' ', fd);
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
	int		id;
	int		ret;
	int		status;
	char	**args;

	if (!cmd)
	{
		close(pipe_in);
		close(std_out);
		return (0);
	}
	signal(SIGQUIT, SIG_DFL);
	id = fork();
	if (id)
	{
		if (cmd->file)
			close(cmd->file);
		close(pipe_in);
		close(std_out);
		close(STDOUT_FILENO);
		wait(&status);
		return (WEXITSTATUS(status));
	}
	args = ft_split_cmd_args(shell_c, cmd->str, cmd->fd);
	if (args == NULL)
		return (-1);
	if (args[0] != NULL)
	{

		if (cmd->separator == PIPE) // case where there is > and pipe don't work
		{
			pipe(cmd->fd);
			if (cmd->from_to == BRACKET_TO)
			{
				dup2(cmd->file, STDOUT_FILENO);
				close(cmd->file);
				close(cmd->fd[1]);
			}
			else
			{
				dup2(cmd->fd[1], STDOUT_FILENO);
				close(cmd->fd[1]);
			}
		}
		else
		{
			if (cmd->from_to == BRACKET_TO)
			{
				//close(std_out);
				//std_out = cmd->file;
				dup2(cmd->file, STDOUT_FILENO);
				close(cmd->file);
			}
			else
				dup2(std_out, STDOUT_FILENO);
			//close(std_out);
		}
		if (cmd->from_to == BRACKET_FROM)
		{
			dup2(cmd->file, STDIN_FILENO);
			close(cmd->file);
			//close(pipe_in); //maybe usefull
		}
		else
		{
			dup2(pipe_in, STDIN_FILENO);
			if (pipe_in != STDIN_FILENO)
				close(pipe_in);
		}
		ret = ft_route_command(args[0], &args[1], cmd->fd, args, shell_c, cmd);
		close(STDIN_FILENO);
		ft_recursiv_command(cmd->next, shell_c, cmd->fd[0], std_out);
		exit(ret);
	}
	return (0);
}

// depreciated
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
		args = ft_split_cmd_args(shell_c, cmdi->str, cmdi->fd);
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
