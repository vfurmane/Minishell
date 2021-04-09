/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 12:08:49 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/09 10:36:03 by earnaud          ###   ########.fr       */
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

int ft_unset(char **args, int fd)
{
	(void)fd;
	int count[3];

	count[0] = 0;
	while (args[count[0]])
	{
		count[1] = 0;
		count[2] = in_it(args[count[0]], environement);
		if (!count[2])
			count[0]++;
		else
		{
			while(count[2] <= (int)ft_strstrlen(environement))
			{
				environement[count[2]] = environement[count[2] + 1];
				count[2]++;
			}
			free(environement[count[2]]);
		}
	}
	copy_env(environement, NULL);
	//free all
	 	exit(S_SIGUPENV);
	return (0);
}
