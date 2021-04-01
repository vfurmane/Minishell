/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 14:26:42 by earnaud           #+#    #+#             */
/*   Updated: 2021/04/01 12:28:52 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// int ft_sub_echo(int n, char *str, int fd)
// {
// 	int id = fork();
// 	if (!id)
// 		return ft_echo(n, str, fd);
// 	else
// 		return (0);
// }

int checkflag(const char *str)
{
	if (!ft_strnstr(str, "-n", ft_strlen(str)))
		return (0);
	return (1);
}

int ft_echo(const char **str, int fd)
{
	size_t i;
	int n;
	int id;

	id = fork();
	if (id)
		return (0);
	i = 0;
	n = checkflag(*str);
	if (n)
		str++;
	else
		write(fd, "\n", 1);
	while (*str)
	{
		while (*str[i])
		{
			if (*str[i] == '\n' && !*str[i + 1] && n)
				break;
			write(fd, *str + i++, 1);
		}
		str++;
	}
	return (0);
}