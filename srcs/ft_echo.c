/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 14:26:42 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/31 17:20:39 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int ft_sub_echo(int n, char *str, int fd)
{
	int id = fork();
	if (!id)
		return ft_echo(n, str, fd);
	else
		return (0);
}

int ft_echo(int n, char *str, int fd)
{
	size_t i = 0;
	while (str[i])
	{
		if (str[i] == '\n' && !str[i + 1] && n)
			break;
		write(fd, str + i++, 1);
	}
	return (0);
}