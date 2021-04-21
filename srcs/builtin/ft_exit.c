/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 12:09:19 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/21 10:52:03 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int ft_exit(char **args, int fd, t_config *shell_c)
{
	(void)args;
	(void)fd;
	write(fd, "exit\n", 5);
	write(shell_c->fd[1], EXIT_SHELL, 3);
	write(shell_c->fd[1], "\x1F\x1E", 2);
	return (0);
}
