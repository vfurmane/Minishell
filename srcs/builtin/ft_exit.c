/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 12:09:19 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/13 17:31:17 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int ft_exit(char **args, int fd)
{
	(void)args;
	(void)fd;
	write(fd, "exit\n", 6);
	exit(S_SIGQUITSH);
	return (0);
}
