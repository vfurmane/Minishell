/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 12:03:06 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/23 12:10:34 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

int	ft_navigate_history(t_config *shell_c, t_icanon *icanon)
{
	tputs(tgoto(column_address, 0, ft_strlen(shell_c->prompt)), 1, ft_putchar);
	tputs(clr_eol, 1, ft_putchar);
	if (icanon->buffer[2] == 'A')
		shell_c->history = shell_c->history->next;
	else if (icanon->buffer[2] == 'B')
		shell_c->history = shell_c->history->previous;
	icanon->line = shell_c->history->content;
	icanon->line_i = ft_strlen(icanon->line);
	icanon->column = 0;
	ft_rewrite_line(icanon, 1);
	icanon->column = icanon->line_i;
	return (0);
}

int	ft_escape_code(t_config *shell_c, t_icanon *icanon)
{
	if (icanon->buffer[2] == 'D' && icanon->column > 0)
	{
		tputs(tgoto(cursor_left, 0, 0), 1, ft_putchar);
		(icanon->column)--;
	}
	else if (icanon->buffer[2] == 'C' && icanon->column < icanon->line_i)
	{
		tputs(tgoto(cursor_right, 0, 0), 1, ft_putchar);
		(icanon->column)++;
	}
	else if ((icanon->buffer[2] == 'A' && shell_c->history->next != NULL) ||
			(icanon->buffer[2] == 'B' && shell_c->history->previous != NULL))
		ft_navigate_history(shell_c, icanon);
	else
		tputs(bell, 1, ft_putchar);
	return (0);
}
