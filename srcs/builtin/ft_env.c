/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 12:09:05 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/04 11:25:49 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int ft_env(char **args, int fd, char **environment)
{
	int i;

	i = 0;
	if (args[0] != NULL)
		return (ft_stderr_message("env: too many arguments", NULL, NULL, 1));
	while (environment[i])
	{
		if (ft_strchr(environment[i], '='))
		{
			write(fd, environment[i], ft_strlen(environment[i]));
			write(fd, "\n", 1);
		}
		i++;
	}
	return (0);
}
