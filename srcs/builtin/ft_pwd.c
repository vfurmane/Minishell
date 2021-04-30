/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 13:44:05 by earnaud           #+#    #+#             */
/*   Updated: 2021/04/30 11:42:19 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pwd(char **str, int fd)
{
	(void)str; /* ===== DELETE ===== */
	write(fd, getenv("PWD"), ft_strlen(getenv("PWD")));
	write(fd, "\n", 1);
	return (0);
}
