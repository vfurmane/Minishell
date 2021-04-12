/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 12:08:49 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/12 16:44:53 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

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

static int in_it(char *new, char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		if (str_in_str(new, env[i]))
			return (i);
		i++;
	}
	return (0);
}

int ft_unset(char **args, int fd, int need_quit)
{
	(void)fd;
	int count[3];
	char *to_free;

	count[0] = 0;
	while (args[count[0]])
	{
		count[1] = 0;
		count[2] = in_it(args[count[0]], environement);
		if (count[2])
		{
			to_free = environement[count[2]];
			while (count[2] <= (int)ft_strstrlen(environement))
			{
				environement[count[2]] = environement[count[2] + 1];
				count[2]++;
			}
			free(to_free);
			free(environement[count[2]]);
		}
		count[0]++;
	}
	if (need_quit)
	{
		copy_env(environement, NULL);
		exit(S_SIGUPENV);
	}
	return (0);
}
