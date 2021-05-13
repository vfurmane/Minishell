/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 14:34:59 by earnaud           #+#    #+#             */
/*   Updated: 2021/05/13 14:39:46 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*buffer_fix(char *const buffer)
{
	char *str;
	int count[2];

	count[0] = 0;
	count[1] = 0;
	str = malloc(sizeof(char) * ft_strlen(buffer)); //check if fail
	if (!str)
		return (NULL);
	while (buffer[count[0]] && !ft_strchr(";|", buffer[count[0]]))
	{
		if (ft_strchr("<>", buffer[count[0]]))
		{
			while (ft_strchr(" <>", buffer[count[0]]))
				count[0]++;
			while (buffer[count[0]] && !ft_strchr(" <>|;", buffer[count[0]]))
				count[0]++;
		}
		//else
			str[count[1]++] = buffer[count[0]++];
	}
	str[count[1]] = 0;
	return (str);
}

char		*ft_fix_openfiles(t_config *shell_c, char *const buffer, t_cmd *cmd, int *error)
{
	// char *file_name;
	// char *file_name_fix;
	 int i;
	// int happen;
	// char *temp;

	if (!buffer)
		return (0);
	i = 0;
	cmd->file = 0;
	//happen = 0;
	while (buffer[i] && !ft_strchr("|;", buffer[i]))
	{
		if (ft_strchr("<>", buffer[i]))
		{
			if (pars_files(buffer, shell_c, cmd, &i) == -1)
			 {
				 *error = 1;
				 return (NULL);
			 }
			// old way of doing things
			//
			// if (buffer[i] == '<')
			// 	cmd->from_to = BRACKET_FROM;
			// else if (buffer[i] == '>')
			// 	cmd->from_to = BRACKET_TO;
			// if (buffer[i + 1] == '>')
			// {
			// 	happen = 1;
			// 	i++;
			// }
			// i++;
			// if (cmd->file)
			// 	close(cmd->file);
			// while (buffer[i] == ' ')
			// 	i++;
			// file_name = ft_strndup(buffer + i, where_to_cut(buffer + i));
			// if (file_name[0] != '/' || file_name[0] != '~')
			// {
			// 	temp = ft_strjoin(ft_getenv(shell_c->envp_list, "PWD"), "/"); //check if null
			// 	file_name_fix = ft_strjoin(temp, file_name);				  //check if null
			// 	free(temp);
			// }
			// else
			// 	file_name_fix = file_name;
			//
			// if (cmd->from_to == BRACKET_FROM)
			// {
			// 	cmd->file = open(file_name_fix, O_RDWR);
			// 	if (cmd->file == -1)
			// 		return (error_file(file_name, file_name_fix, error));
			// }
			// else if (happen)
			// {
			// 	cmd->file = open(file_name_fix, O_RDWR | O_APPEND | O_CREAT, 0666);
			// 	if (cmd->file == -1)
			// 		return (error_file(file_name, file_name_fix, error));
			// }
			// else
			// {
			// 	cmd->file = open(file_name_fix, O_RDWR | O_CREAT, 0666);
			// 	if (cmd->file == -1)
			// 		return (error_file(file_name, file_name_fix, error));
			// }
			// free(file_name);
			// free(file_name_fix);
		}
		else
			i++;
	}
	if (cmd->file)
		return (buffer_fix(buffer));
	return (NULL);
}