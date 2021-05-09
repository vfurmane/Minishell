/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 13:44:05 by earnaud           #+#    #+#             */
/*   Updated: 2021/05/09 11:52:25 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pwd(t_config *shell_c, char **args, int output_fd)
{
	char	*pwd;

	(void)shell_c; /* ===== DELETE ===== */
	(void)args; /* ===== DELETE ===== */
	pwd = getcwd(NULL, 0);
	write(output_fd, pwd, ft_strlen(pwd));
	write(output_fd, "\n", 1);
	free(pwd);
	return (0);
}
