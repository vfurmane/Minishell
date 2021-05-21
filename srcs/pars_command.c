/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 14:34:59 by earnaud           #+#    #+#             */
/*   Updated: 2021/05/20 15:18:00 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*buffer_fix(char *const buffer)
{
	char *str;
	int count[2];

	count[0] = 0;
	count[1] = 0;
	str = malloc(sizeof(char) * ft_strlen(buffer)); //protec
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
		str[count[1]++] = buffer[count[0]++];
	}
	str[count[1]] = 0;
	return (str);
}

char		*ft_fix_openfiles(t_config *shell_c, char *const buffer, t_cmd *cmd, int *error)
{
	 int i;
	 int bslash;
	 
	 bslash = 0;
	 if (!buffer)
		 return (0);
	 i = 0;
	 while (buffer[i] && !ft_strchr("|;", buffer[i]))
	 {
		 if (buffer[i] == '\\')
		 {
			 i++;
			 bslash = 1;
		 }
		 if (buffer[i] == '"')
		 {
			 i++;
			 while (buffer[i] != '"' && buffer[i] && !bslash)
				 i++;
			 bslash = 0;
		 }
		 if (buffer[i] == '\'')
		 {
			 i++;
			 while (buffer[i] != '\'' && buffer[i] && !bslash)
				 i++;
			 bslash = 0;
		 }
		 if (ft_strchr("<>", buffer[i]))
		 {
			 if (pars_files(buffer, shell_c, cmd, &i) == -1)
			 {
				 *error = 1;
				 return (NULL);
			 }
		 }
		 else if (buffer[i])
		 {
			 i++;
			 bslash = 0;
		 }
	 }
	if (cmd->file_from || cmd->file_to)
		return (buffer_fix(buffer));
	return (NULL);
}