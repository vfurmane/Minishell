/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 14:34:59 by earnaud           #+#    #+#             */
/*   Updated: 2021/05/28 14:19:30 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int skip_dquote(const char *str, int *i, int *bslash)
{
	*bslash = 0;
	if (str[*i] == '\\')
	{
		*bslash = 1;
		(*i)++;
	}
	if (str[*i] == '"' && !(*bslash))
	{
		*bslash = 0;
		(*i)++;
		while (str[*i] != '"')
		{
			if (str[*i] == '\\')
			{
				*bslash = 1;
				(*i)++;
			}
			if (!str[*i] && !(*bslash))
				return (ft_stderr_message("Error: ", "unterminated quote", NULL, -1));
			(*i)++;
		}
	}
	return (0);
}

int	skip_quotes(const char *str, int *i)
{
	int bslash;

	if (skip_dquote(str, i, &bslash) == -1)
		return (-1);
	if (str[*i] == '\'' && !bslash)
	{
		bslash = 0;
		(*i)++;
		while (str[*i] != '\'')
		{
			if (str[*i] == '\\')
			{
				bslash = 1;
				(*i)++;
			}
			if (!str[*i] && !bslash)
				return (ft_stderr_message("Error: ", "unterminated quote", NULL, -1));
			(*i)++;
		}
	}
	return (0);
}

char	*buffer_fix(char *const buffer)
{
	char	*str;
	int		count[3];

	count[0] = 0;
	count[1] = 0;
	str = malloc(sizeof(char) * ft_strlen(buffer));
	if (!str)
		return (NULL);
	while (buffer[count[0]] && !ft_strchr(";|", buffer[count[0]]))
	{
		count[2] = count[0];
		skip_quotes(buffer, count + 2); // check error
		while (count[0] < count[2])
			str[count[1]++] = buffer[count[0]++];
		if (ft_strchr("<>", buffer[count[0]]))
		{
			while (ft_strchr(" <>", buffer[count[0]]))
				count[0]++;
			skip_quotes(buffer, count); // check error
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

	 if (!buffer)
		 return (0);
	 i = 0;
	 while (buffer[i] && !ft_strchr("|;", buffer[i]))
	 {
		 if (skip_quotes(buffer, &i))
		 {
			 free(buffer);
			 free_shell(shell_c);
			 free_all_cmd(cmd);
			 exit(-1);
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
			 i++;
	 }
	 if (cmd->file_from || cmd->file_to)
		 return (buffer_fix(buffer));
	 return (NULL);
}