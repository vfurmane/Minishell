/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 12:08:23 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/18 19:17:39 by vfurmane         ###   ########.fr       */
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

/*static void ft_free_neo(char **neo)
{
	size_t i;

	i = 0;
	if (neo)
	{
		while (neo[i])
			free(neo[i++]);
		free(neo);
	}
}*/

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

void ft_print_exp_list(char **args, int fd, t_kvpair *envp_list)
{
	/*int i;
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
	exit(0);*/
	int			key_len;
	t_kvpair	*envp_elm;

	if (*args) // Keeping from old function
	{
		write(fd, "\n", 1);
		exit(0);
	}
	envp_elm = envp_list;
	while (envp_elm)
	{
		write(fd, "declare -x ", 12);
		key_len = ft_strlen(envp_elm->key);
		write(fd, envp_elm->key, key_len);
		if (envp_elm->value != NULL)
		{
			write(fd, "=\"", 2);
			write(fd, &envp_elm->value[1], ft_strlen(envp_elm->value) - 1);
			write(fd, "\"", 1);
		}
		write(fd, "\n", 1);
		envp_elm = envp_elm->next;
	}
	exit(0); /* ===== DELETE ===== */
}

int ft_export(char **args, int fd, t_config *shell_c)
{
	int		i;

	if (*args == NULL)
		ft_print_exp_list(args, fd, shell_c->envp_list); // Why passing *args if it is NULL ?
	i = 0;
	while (args[i])
	{
		write(shell_c->fd[1], ADD_ENV, 3);
		write(shell_c->fd[1], "\x1F", 1);
		write(shell_c->fd[1], args[i], ft_strlen(args[i]));
		write(shell_c->fd[1], "\x1E", 1);
		i++;
	}
	exit(0);
	return (0);
}
