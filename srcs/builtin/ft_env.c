/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 12:09:05 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/18 18:00:50 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int ft_env(char **args, int fd, char **environment)
{
	int i;

	i = 0;
	if (*args)
	{
		write(fd, "\n", 1);
		return (0);
	}
	while (environment[i])
	{
		if (ft_strchr(environment[i], '='))
		{
			write(fd, environment[i], ft_strlen(environment[i]));
			write(fd, "\n", 1);
		}
		i++;
	}
	exit(0);
	return (0);
}
