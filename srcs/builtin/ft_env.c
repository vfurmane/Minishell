/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 12:09:05 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/06 14:30:01 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_env(char **args, int fd)
{
	(void)args;
	(void)fd;
	int i;
	i = 0;
	while (environement[i])
	{
		write(fd, environement[i], ft_strlen(environement[i]));
		write(fd, "\n", 1);
		i++;
	}
	return (0);
}
