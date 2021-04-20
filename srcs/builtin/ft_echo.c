/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 14:26:42 by earnaud           #+#    #+#             */
/*   Updated: 2021/04/20 14:57:44 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

typedef struct	s_echo
{
	int			e_flag;
	int			e_cap_flag;
	int			n_flag;
}				t_echo;

static int	ft_parse_echo_args(t_echo *echo_c, char **args)
{
	int		i;
	int		j;
	t_echo	tmp_echo_c;

	ft_bzero(&tmp_echo_c, sizeof(tmp_echo_c));
	tmp_echo_c.e_cap_flag = 1;
	i = -1;
	while (args[++i][0] == '-')
	{
		j = 0;
		while (args[i][++j])
		{
			if (args[i][j] == 'e' || args[i][j] == 'E')
			{
				tmp_echo_c.e_flag = args[i][j] == 'e';
				tmp_echo_c.e_cap_flag = args[i][j] == 'E';
			}
			else if (args[i][j] == 'n')
				tmp_echo_c.n_flag = 1;
			else
				return (i);
		}
	}
	ft_memcpy(echo_c, &tmp_echo_c, sizeof(tmp_echo_c));
	return (i);
}

int			ft_echo(char **args, int fd)
{
	int		i;
	t_echo	echo_c;

	i = ft_parse_echo_args(&echo_c, args);
	while (args[i])
	{
		write(fd, args[i], ft_strlen(args[i]));
		if (args[++i] != NULL)
			write(fd, " ", 1);
	}
	if (!echo_c.n_flag)
		write(fd, "\n", 1);
	return (0);
}
