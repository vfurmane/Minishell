/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 14:26:42 by earnaud           #+#    #+#             */
/*   Updated: 2021/05/26 13:30:54 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	ft_parse_echo_args(t_echo *echo_c, char **args)
{
	int		i;
	int		j;
	t_echo	tmp_echo_c;

	ft_bzero(&tmp_echo_c, sizeof(tmp_echo_c));
	tmp_echo_c.e_cap_flag = 1;
	i = 0;
	while (args[i] && args[i][0] == '-')
	{
		j = 0;
		while (args[i][++j])
		{
			if (args[i][j] == 'n')
				tmp_echo_c.n_flag = 1;
			else
				return (i);
		}
		i++;
	}
	ft_memcpy(echo_c, &tmp_echo_c, sizeof(tmp_echo_c));
	return (i);
}

int	ft_echo(t_config *shell_c, char **args, int output_fd)
{
	int		i;
	t_echo	echo_c;

	(void)shell_c;
	i = ft_parse_echo_args(&echo_c, args);
	while (args[i])
	{
		write(output_fd, args[i], ft_strlen(args[i]));
		if (args[++i] != NULL)
			write(output_fd, " ", 1);
	}
	if (!echo_c.n_flag)
		write(output_fd, "\n", 1);
	return (0);
}
