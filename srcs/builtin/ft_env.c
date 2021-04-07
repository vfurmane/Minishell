/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 12:09:05 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/07 10:24:13 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int ft_env(char **args, int fd)
{
	int i;
	i = 0;
	if (*args)
	{
		write(fd, "\n", 1);
		return (0);
	}
	while (environement[i])
	{
		write(fd, environement[i], ft_strlen(environement[i]));
		write(fd, "\n", 1);
		i++;
	}
	return (0);
}
