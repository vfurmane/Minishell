/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 12:09:05 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/12 12:30:40 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int ft_env(char **args, int fd, char **environement)
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
	exit(0);
	return (0);
}
