/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 13:44:05 by earnaud           #+#    #+#             */
/*   Updated: 2021/05/04 10:17:34 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pwd(char **str, int fd)
{
	char	*pwd;

	(void)str; /* ===== DELETE ===== */
	pwd = getcwd(NULL, 0);
	write(fd, pwd, ft_strlen(pwd));
	write(fd, "\n", 1);
	free(pwd);
	return (0);
}
