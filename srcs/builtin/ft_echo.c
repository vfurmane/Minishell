/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 14:26:42 by earnaud           #+#    #+#             */
/*   Updated: 2021/04/01 15:24:32 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int checkflag(char *args)
{
	if (!ft_strnstr(args, "-n", ft_strlen(args)))
		return (0);
	return (1);
}

int ft_echo(char **args, int fd)
{
	size_t i;
	int n;
	int id;

	id = fork();
	if (id)
		return (0);
	i = 0;
	n = checkflag(*args);
	if (n)
		args++;
	else
		write(fd, "\n", 1);
	while (*args)
	{
		while (*args[i])
		{
			if (*args[i] == '\n' && !*args[i + 1] && n)
				break;
			write(fd, *args + i++, 1);
		}
		args++;
	}
	return (0);
}