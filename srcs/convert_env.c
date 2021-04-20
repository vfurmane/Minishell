/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 16:49:20 by earnaud           #+#    #+#             */
/*   Updated: 2021/04/13 14:03:28 by earnaud          ###   ########.fr       */
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

static int str_in_str(char *new, char *env)
{
	int i;
	i = 0;
	while (new[i])
	{
		if (!env[i])
			return (0);
		if (new[i] != env[i])
			return (0);
		i++;
	}
	if (env[i] != '=')
		return (0);
	return (1);
}

char *ft_getenv(char **env, char *str)
{
	int i;

	i = 0;
	while (*env)
	{
		if (str_in_str(str, *env))
		{
			while (*((*env) + i))
			{
				if ((*env)[i] == '=')
					return ((*env) + i + 1);
				i++;
			}
		}
		env++;
	}
	return (0);
}

char *ft_convert_env(char *source, char **env)
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
			i += ft_strlcpy(result + i, ft_getenv(env, temp), ft_strlen(ft_getenv(env, temp)) + 1);
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

char *ft_exportenv(const char *str, int *str_i, char **environment)
{
	int i;
	char *env;
	char *env_name;

	i = 0;
	while (ft_isalpha(str[i]) || (ft_isdigit(str[i] && i > 0)) || str[i] == '_')
		i++;
	*str_i += i;
	env_name = malloc(sizeof(*env) * (i + 1));
	if (env_name == NULL)
		return (NULL);
	ft_strlcpy(env_name, str, i + 1);
	env = ft_getenv(environment, env_name);
	free(env_name);
	if (env == NULL)
		env = "";
	return (env);
}
