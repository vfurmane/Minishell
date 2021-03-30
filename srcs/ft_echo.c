/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 14:26:42 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/30 17:06:34 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

int ft_echo(int n, char *str, int fd)
{
	int i = 0;
	while (str[i] && (!n || i <= ft_strlen(str)))
	{
		write(fd, str + i++, 1);
	}
	return (0);
}