/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 16:49:20 by earnaud           #+#    #+#             */
/*   Updated: 2021/04/02 11:37:15 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_ifenv(char *source)
{
	char temp[ARG_MAX + 1];
	int i;

	source++;
	i = 0;
	while (*source != ' ' && *source != '\n' && *source)
		temp[i++] = *source++;
	if (!getenv(temp))
		return (0);
	else
		return (1);
}

char *ft_convert_env(char *source)
{
	int i;
	int j;
	char temp[ARG_MAX + 1];
	char *result;

	i = 0;
	result = malloc(ARG_MAX + 1);
	while (*source)
	{
		j = 0;
		*temp = 0;
		if (*source == '$' && ft_ifenv(source))
		{
			source++;
			while (*source != ' ' && *source != '\n' && *source)
				temp[j++] = *source++;
			i += ft_strlcpy(result + i, getenv(temp), ft_strlen(getenv(temp)) + 1);
		}
		else
		{
			result[i] = *source;
			source++;
			i++;
		}
		temp[j] = 0;
	}
	result[i] = 0;
	return (result);
}

char	*ft_getenv(const char *str, char *new_str, int *str_i, int *new_str_i)
{
	int		i;
	char	*env;
	char	*env_name;
	int		env_len;

	i = 0;
	while (ft_isalpha(str[i]) || (ft_isdigit(str[i] && i > 0)) || str[i] == '_')
		i++;
	*str_i += i;
	env_name = malloc(sizeof(*env) * (i + 1));
	if (env_name == NULL)
		return (NULL);
	ft_strlcpy(env_name, str, i + 1);
	env = getenv(env_name);
	env_len = ft_strlen(env);
	ft_strlcpy(new_str, env, env_len + 1);
	*new_str_i += env_len;
	free(env_name);
	return (env);
}
