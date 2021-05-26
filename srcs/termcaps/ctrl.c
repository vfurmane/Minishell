/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 12:10:55 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/26 14:28:12 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

int	ft_ctrl_d(t_config *shell_c, t_icanon *icanon)
{
	if (icanon->line_i == 0)
	{
		ft_exit(shell_c, NULL, 1);
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

int	ft_ctrl_ae(t_config *shell_c, t_icanon *icanon)
{
	if (icanon->buffer[0] == 1)
	{
		tputs(tgoto(column_address, 0, shell_c->start_column), 1,
			ft_putchar);
		icanon->column = 0;
	}
	else if (icanon->buffer[0] == 5)
	{
		tputs(tgoto(column_address, 0,
				shell_c->start_column + icanon->line_i), 1, ft_putchar);
		icanon->column = icanon->line_i;
	}
	return (0);
}

int	ft_ctrl_ku(t_config *shell_c, t_icanon *icanon)
{
	if (icanon->buffer[0] == 11)
	{
		ft_bzero(icanon->line + icanon->column,
			icanon->line_i - icanon->column);
		icanon->line_i = ft_strlen(icanon->line);
		icanon->column = icanon->line_i;
		tputs(tgoto(column_address, 0,
				shell_c->start_column + icanon->line_i), 1, ft_putchar);
	}
	else if (icanon->buffer[0] == 21)
	{
		icanon->line_i = ft_strlen(icanon->line + icanon->column);
		ft_memmove(icanon->line, icanon->line + icanon->column, icanon->line_i);
		ft_bzero(icanon->line + icanon->column, icanon->line_i);
		icanon->column = 0;
		tputs(tgoto(column_address, 0,
				shell_c->start_column), 1, ft_putchar);
	}
	return (1);
}
