/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 12:08:49 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/18 13:06:52 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int str_in_str(char *new, char *env, int exp_list)
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
	if (!exp_list)
	{
		if (env[i] != '=')
			return (0);
	}
	else
	{
		if (env[i])
			return (0);
	}
	return (1);
}

static int in_it(char *new, char **env, int exp_list)
{
	int i;

	i = 0;
	while (env[i])
	{
		if (str_in_str(new, env[i], exp_list))
			return (i);
		i++;
	}
	return (0);
}

static void unset_env(char **args, char **environment, int exp_list)
{
	int count[3];
	char *to_free;

	count[0] = 0;
	while (args[count[0]])
	{
		count[1] = 0;
		count[2] = in_it(args[count[0]], environment, exp_list);
		if (count[2])
		{
			to_free = environment[count[2]];
			while (count[2] <= (int)ft_arrlen(environment))
			{
				environment[count[2]] = environment[count[2] + 1];
				count[2]++;
			}
			free(to_free);
			free(environment[count[2]]);
		}
		count[0]++;
	}
}

int ft_unset(char **args, int fd, int need_quit, t_config *shell_c, int pipefd[2])
{
	char	**environment;

	environment = shell_c->envp; /* ===== DELETE ===== */
	(void)fd;
	unset_env(args, environment, 0);
	unset_env(args, export_list, 1);
	if (need_quit == 1)
	{
		copy_env(environment, NULL, environment, pipefd);
		copy_env(export_list, NULL, export_list, pipexport);
		exit(S_SIGUPENV);
	}
	return (0);
}
