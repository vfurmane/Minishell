/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 13:32:16 by earnaud           #+#    #+#             */
/*   Updated: 2021/04/19 13:50:31 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int flag(char *str)
{
	if (ft_strchr(str, '-'))
		return (1);
	return (0);
}

int ft_cd(char **str, int fd, char **envp)
{
	fd = 0;
	if (str[1] && flag(str[1]) && !str[2])
		return (chdir(ft_getenv(envp, "OLDPWD")));
	if (!str)
		return (chdir("~"));
	return (chdir(*str));
}
