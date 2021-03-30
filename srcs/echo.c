/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 14:26:42 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/30 14:28:54 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

static int env_write(char *str, int fd)
{
	int i = 0;
	char str2[ARG_MAX];
	while (*(str + i) && *(str + i) != ' ' && *(str + i) != '\n')
	{
		str2[i] = *(str + i);
		i++;
	}
	str2[i] = '\0';
	write(fd, getenv(str2), ft_strlen(getenv(str2)));
	return (i + 1);
}

int ft_echo(int n, char *str, int fd)
{
	int i = 0;
	while (str[i] && (!n || i <= ft_strlen(str)))
	{
		if (str[i] == '$')
			i += env_write(str + i + 1, fd);
		write(fd, str + i++, 1);
	}
	return (0);
}