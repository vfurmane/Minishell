/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 12:09:05 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/09 11:48:01 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int ft_env(t_config *shell_c, char **args, int output_fd)
{
	int		i;
	char	**environment;

	environment = shell_c->envp;
	i = 0;
	if (args[0] != NULL)
		return (ft_stderr_message("env: too many arguments", NULL, NULL, 1));
	while (environment[i])
	{
		if (ft_strchr(environment[i], '='))
		{
			write(output_fd, environment[i], ft_strlen(environment[i]));
			write(output_fd, "\n", 1);
		}
		i++;
	}
	return (0);
}
