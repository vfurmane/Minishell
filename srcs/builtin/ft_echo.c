/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 14:26:42 by earnaud           #+#    #+#             */
/*   Updated: 2021/04/09 11:57:50 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int checkflag(char *args)
{
	if (!args)
	return (0);
	if (!ft_strnstr(args, "-n", ft_strlen(args)))
		return (0);
	return (1);
}

int ft_echo(char **args, int fd)
{
	size_t i;
	int n;
	char temp;
	
	i = 0;
	n = checkflag(*args);
	if (n)
		args++;
	// else
	// 	write(fd, "\n", 1);
	while (*args)
	{
		while ((*args)[i])
		{
			temp = (*args)[i];
			write(fd, *args + i++, 1);
		}
		args++;
	}
	if (!n)
	write(fd, "\n", 1);
	return (0);
}