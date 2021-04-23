/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 09:59:18 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/23 11:56:48 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

int	ft_route_icanon(t_config *shell_c, t_icanon *icanon)
{
	int			ret;

	ret = 1;
	if (icanon->buffer[0] == 4)
		ret = ft_ctrl_d(shell_c, icanon);
	else if (icanon->buffer[0] >= 32 && icanon->buffer[0] <= 126)
		icanon->line_i = ft_insert_char(icanon);
	else if (icanon->buffer[0] == 127 && icanon->column > 0)
		ft_backspace(icanon);
	else if (icanon->buffer[0] == '\f')
		ft_ctrl_l(shell_c, icanon->line);
	else if (icanon->buffer[0] == '\n')
	{
		ft_putchar('\n');
		return (0);
	}
	else if (icanon->buffer[0] == 27 && icanon->buffer[1] == 91)
		ft_escape_code(shell_c, icanon);
	else
		tputs(bell, 1, ft_putchar);
	if (icanon->buffer[0] != '\n' && icanon->buffer[0] != 27)
		ft_rewrite_line(icanon, 0);
	return (ret);
}

int	ft_read_icanon(t_config *shell_c, t_icanon *icanon)
{
	int			ret;

	ret = 1;
	while (ret > 0 && icanon->line_i < ARG_MAX)
	{
		ret = read(0, icanon->buffer, 3);
		ret = ft_route_icanon(shell_c, icanon);
	}
	icanon->line[icanon->line_i] = '\0'; // Useless
	return (0);
}
