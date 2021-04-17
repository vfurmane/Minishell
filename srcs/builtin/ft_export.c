/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 12:08:23 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/17 14:18:15 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int list_last(char **exp_list, int index)
{
	int i;
	int ret;
	int last;
	char *temp;

	if (ft_strchr(exp_list[index], '='))
		temp = ft_strcdup(exp_list[index], '=');
	else
		temp = ft_strdup(exp_list[index]);
	i = 0;
	last = -1;
	while (exp_list[i])
	{
		if (ft_strnstr(exp_list[i], temp, ft_strlen(temp)))
		{
			if (last == -1)
				last = i;
			if ((ft_strchr(exp_list[last], '=') && ft_strchr(exp_list[i], '=')) || !ft_strchr(exp_list[last], '='))
				last = i;
		}
		i++;
	}
	free(temp);
	ret = (last == index);
	return (ret);
}

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
		if (list_last(args, i))
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
	result = malloc(sizeof(char *) * (ft_arrlen(args) + 1));
	if (!result)
		return (NULL);
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
			result[i] = ft_strcdup(args[i], '=');
		else
			result[i] = ft_strdup(args[i]);
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

int ft_export(char **args, int fd, char **environment, int pipefd[2])
{
	char **temp;
	char **args_fixed;
	//make the error check
	if (!(*args))
		ft_print_exp_list(args, fd, export_list);

	temp = to_unset(args);
	args_fixed = fix_args(args);
	ft_unset(temp, fd, 0, environment, pipefd); //insert here exp_list
	ft_free_neo(temp);
	copy_env(0, args, export_list, pipexport);
	copy_env(0, args_fixed, environment, pipefd);
	free(environment);
	ft_free_neo(args_fixed);
	exit(S_SIGUPENV);
	return (0);
}
