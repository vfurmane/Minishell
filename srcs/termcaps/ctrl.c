/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 12:10:55 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/23 12:12:19 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

int	ft_ctrl_d(t_config *shell_c, t_icanon *icanon)
{
	if (icanon->line_i == 0)
	{
		ft_exit(0, 0, shell_c);
		return (0);
	}
	else if (icanon->column < icanon->line_i)
	{
		icanon->line_i = ft_delete_char(icanon->line, icanon->column + 1);
		tputs(clr_eol, 1, ft_putchar);
		return (1);
	}
	else
		tputs(bell, 1, ft_putchar);
	return (1);
}

int	ft_ctrl_l(t_config *shell_c, char *line)
{
	tputs(save_cursor, 1, ft_putchar);
	tputs(clear_screen, 1, ft_putchar);
	ft_display_prompt(shell_c->prompt);
	write(1, line, ft_strlen(line));
	tputs(restore_cursor, 1, ft_putchar);
	tputs(tgoto(row_address, 0, 0), 1, ft_putchar);
	return (0);
}
