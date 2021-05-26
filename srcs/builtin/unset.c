/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 12:08:49 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/26 13:35:36 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	ft_is_valid_identifier(const char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=' && (ft_isalpha(arg[i])
			|| (ft_isdigit(arg[i]) && i > 0) || arg[i] == '_'))
		i++;
	return (arg[i] == '\0' && i > 0);
}

int	ft_unset(t_config *shell_c, char **args, int output_fd)
{
	int		i;

	(void)output_fd;
	i = 0;
	while (args[i])
	{
		if (ft_is_valid_identifier(args[i]))
			ft_write_pipe(DEL_ENV, args[i], NULL, shell_c->fd[1]);
		else
			ft_stderr_message("unset: `", args[i], "': not a valid identifier",
				0);
		i++;
	}
	return (0);
}
