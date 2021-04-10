/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 12:08:23 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/09 17:40:01 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void copy_env(char **new_env, char **args)
{
	int i;

	(void)new_env;
	i = 0;
	while (environement[i])
	{
		write(pip[1], environement[i], ft_strlen(environement[i]) + 1);
		i++;
	}
	i = 0;
	while (args && args[i])
	{
		write(pip[1], args[i], ft_strlen(args[i]) + 1);
		i++;
	}
	write(pip[1], "\0", 1);
}

// static int in_it(char *new, char **env)
// {
// 	int i;

// 	i = 0;
// 	while (env[i])
// 	{
// 		if (str_in_str(new, env[i]))
// 			return (i);
// 		i++;
// 	}
// 	return (0);
// }

char *ft_strcdup(const char *str, int chr)
{
	int str_len;
	char *new_str;
	char *first_chr;

	first_chr = ft_strchr(str, chr);
	str_len = first_chr - str;
	if (!(new_str = malloc(sizeof(*new_str) * (str_len + 1))))
		return (NULL);
	new_str = ft_memcpy(new_str, str, sizeof(*new_str) * str_len);
	new_str[str_len] = '\0';
	return (new_str);
}

char **to_unset(char **args)
{
	char **result;
	int i;

	i = 0;
	result = malloc(sizeof(char *) * (ft_strstrlen(args) + 1));
	if (!result)
		return (NULL);
	while (args[i])
	{
		result[i] = ft_strcdup(args[i], '=');
		i++;
	}
	result[i] = 0;
	return (result);
}

static void ft_free_neo(char **neo)
{
	size_t i;

	i = 0;
	if (neo)
	{
		while (neo[i])
			free(neo[i++]);
		free(neo);
	}
}

char **fix_args(char **args)
{
	int many_valid;
	int i;
	int j;
	char **res;

	i = 0;
	j = 0;
	many_valid = 0;
	while (args[i])
	{
		if (args[i][0] != '=' && ft_strchr(args[i], '='))
			many_valid++;
		i++;
	}
	res = malloc(sizeof(char *) * (many_valid + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (args[i])
	{
		if (args[i][0] != '=' && ft_strchr(args[i], '='))
			res[j++] = args[i];
		i++;
	}
	res[j] = 0;
	return (res);
}

int ft_export(char **args, int fd)
{
	char **new_env;
	char **temp;
	char **args_fixed;
	//make the error check
	(void)fd;

	args_fixed = fix_args(args);
	temp = to_unset(args_fixed);
	ft_unset(temp, fd, 0);
	ft_free_neo(temp);

	new_env = malloc(sizeof(char *) * (ft_strstrlen(environement) + ft_strstrlen(args_fixed) + 1));
	if (!new_env)
		return (0);
	copy_env(new_env, args_fixed);
	free(environement);
	ft_free_neo(args_fixed);
	//environement = new_env;
	exit(S_SIGUPENV);
	return (0);
}
