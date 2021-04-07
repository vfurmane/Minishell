/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 12:08:23 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/07 16:04:32 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void copy_env(char **new_env, char **args)
{
	int i;
	
	i = 0;
	while (environement[i])
	{
		write(pip[1], environement[i], ft_strlen(environement[i]) + 1);
		i++;
	}
	i = 0;
	while (*args)
	{
		write(pip[1], args[i], ft_strlen(args[i]) + 1);
		i++;
	}
}

int ft_export(char **args, int fd)
{
	(void)fd;
	char **new_env;
	//make the error check
	new_env = malloc(sizeof(char *) * (ft_strstrlen(environement) + ft_strstrlen(args) + 1));
	if (!new_env)
		return (0);
	copy_env(new_env, args);
	free(environement);
	environement = new_env;
	return (0);
}