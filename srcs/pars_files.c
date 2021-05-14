/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 13:31:40 by earnaud           #+#    #+#             */
/*   Updated: 2021/05/14 17:10:01 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int error_file(char *file_name, char *file_name_fix)
{
	ft_stderr_message(file_name, ": ", strerror(errno), 0);
	free(file_name);
	free(file_name_fix);
	return (-1);
}

int where_to_cut(char *const buffer)
{
	int i;

	i = 0;
	if (!buffer)
		return (0);
	while (buffer[i])
	{
		if (ft_strchr(";| ", buffer[i]))
			return (i);
		i++;
	}
	return (i);
}

int		open_file(t_cmd *cmd, char *file_name_fix, char *file_name, int happen)
{
	if (cmd->from_to == BRACKET_FROM)
	{
		cmd->file_from = open(file_name_fix, O_RDWR);
		if (cmd->file_from == -1)
			return (error_file(file_name, file_name_fix));
	}
	else if (happen)
	{
		cmd->file_to = open(file_name_fix, O_RDWR | O_APPEND | O_CREAT, 0666);
		if (cmd->file_to == -1)
			return (error_file(file_name, file_name_fix));
	}
	else
	{
		cmd->file_to = open(file_name_fix, O_RDWR | O_CREAT, 0666);
		if (cmd->file_to == -1)
			return (error_file(file_name, file_name_fix));
	}
	free(file_name);
	free(file_name_fix);
	return (0);
}

char	*get_file_name_fix(t_config *shell_c, char *file_name)
{
	char *temp;
	char *file_name_fix;

	temp = ft_strjoin(ft_getenv(shell_c->envp_list, "PWD"), "/"); //check if null
	file_name_fix = ft_strjoin(temp, file_name);				  //check if null
	free(temp);
	return file_name_fix;
}

int		pars_files(char *const buffer, t_config *shell_c , t_cmd *cmd, int *i)
{
	int happen;
	char *file_name[2];

	happen = 0;
	if (buffer[*i] == '<')
		cmd->from_to = BRACKET_FROM;
	else if (buffer[*i] == '>')
		cmd->from_to = BRACKET_TO;
	if (buffer[*i + 1] == '>')
	{
		happen = 1;
		(*i)++;
	}
	(*i)++;
	if (cmd->file_from && cmd->from_to == BRACKET_FROM)
		close(cmd->file_from);
	if (cmd->file_to && cmd->from_to == BRACKET_TO)
		close(cmd->file_to);
	while (buffer[*i] == ' ')
		(*i)++;
	file_name[0] = ft_strndup(buffer + *i, where_to_cut(buffer + *i));
	if (file_name[0][0] != '/' || file_name[0][0] != '~')
		file_name[1] = get_file_name_fix(shell_c, file_name[0]);
	else
		file_name[1] = file_name[0];
	return (open_file(cmd, file_name[1], file_name[0], happen));
}