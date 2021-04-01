/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 13:44:05 by earnaud           #+#    #+#             */
/*   Updated: 2021/04/01 14:29:11 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pwd(char **str, int fd)
{
	if (str)
	{
		write(fd, "\npwd : too many arguments\n", 27);
		return (-1);
	}
	write(fd, "\n", 1);
	write(fd, getenv("PWD"), ft_strlen(getenv("PWD")));
	return (0);
}