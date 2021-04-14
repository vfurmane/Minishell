/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 12:08:23 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/14 16:12:53 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void copy_env(char **new_env, char **args, char **environment, int pipefd[2])
{
	int i;

	(void)new_env;
	i = 0;
	while (environment[i])
	{
		write(pipefd[1], environment[i], ft_strlen(environment[i]) + 1);
		i++;
	}
	i = 0;
	while (args && args[i])
	{
		write(pipefd[1], args[i], ft_strlen(args[i]) + 1);
		i++;
	}
	write(pipefd[1], "\0", 1);
}

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

//to put in different file

static int exp_in_it(char **exp_list, char *str)
{
	int i;

	i = 0;
	while (exp_list[i])
	{
		if (ft_strnstr(exp_list[i], str, ft_strlen(str)))
			return (1);
		i++;
	}
	return (0);
}

char **fix_args_exportl(char **args)
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
		if (args[i][0] != '=' && !ft_strchr(args[i], '=') && !exp_in_it(export_list, args[i]))
			many_valid++;
		i++;
	}
	res = malloc(sizeof(char *) * (many_valid + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (args[i])
	{
		if (args[i][0] != '=' && !ft_strchr(args[i], '=') && !exp_in_it(export_list, args[i]))
			res[j++] = args[i];
		i++;
	}
	res[j] = 0;
	return (res);
}

void ft_to_export_list(char **args, int pipefd[2])
{
	char **exp_list;

	exp_list = fix_args_exportl(args);
	//ft_unset(exp_list, fd, 0, export_list, pipefd);
	copy_env(0, exp_list, export_list, pipefd);
	ft_free_neo(exp_list);
	//free(export_list);
}

void ft_print_exp_list(char **args, int fd, char **exp_list)
{
	int i;
	int j;
	int quote;

	i = 0;
	if (*args)
	{
		write(fd, "\n", 1);
		exit(0);
	}
	while (exp_list[i])
	{
		quote = 0;
		j = 0;
		write(fd, "declare -x ", 12);
		while (exp_list[i][j] && exp_list[i][j])
		{
			write(fd, &exp_list[i][j], 1);
			if (exp_list[i][j] == '=')
			{
				write(fd, "\"", 1);
				quote = 1;
			}
			j++;
		}
		if (quote)
			write(fd, "\"", 1);
		write(fd, "\n", 1);
		i++;
	}
	exit(0);
}

//

int ft_export(char **args, int fd, char **environment, int pipefd[2])
{
	char **new_env;
	char **temp;
	char **args_fixed;
	//make the error check
	if (!(*args))
		ft_print_exp_list(args, fd, export_list);

	ft_to_export_list(args, pipexport);
	args_fixed = fix_args(args);
	temp = to_unset(args_fixed);
	ft_unset(temp, fd, 0, environment, pipefd);
	ft_free_neo(temp);

	new_env = malloc(sizeof(char *) * (ft_strstrlen(environment) + ft_strstrlen(args_fixed) + 1)); //protec the malloc
	if (!new_env)
		return (0);
	copy_env(new_env, args_fixed, environment, pipefd);
	free(environment);
	ft_free_neo(args_fixed);
	//environment = new_env;
	exit(S_SIGUPENV);
	return (0);
}
