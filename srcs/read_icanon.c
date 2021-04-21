/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_icanon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 09:07:52 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/21 12:02:08 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_backspace(t_icanon *icanon)
{
	icanon->line_i = ft_delete_char(icanon->line, (icanon->column)--);
	tputs(tgoto(cursor_left, 0, 0), 1, ft_putchar);
	tputs(clr_eol, 1, ft_putchar);
	return (0);
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
	{
		tputs(tgoto(column_address, 0, ft_strlen(shell_c->prompt)), 1,
				ft_putchar);
		tputs(clr_eol, 1, ft_putchar);
		icanon->line = shell_c->history->next->content;
		icanon->line_i = ft_strlen(icanon->line);
		icanon->column = 0;
	}
	else
		tputs(bell, 1, ft_putchar);
	return (0);
}

int	ft_read_icanon(t_config *shell_c, t_icanon *icanon)
{
	int			ret;

	ret = 1;
	while (ret > 0 && icanon->line_i < ARG_MAX)
	{
		ret = read(0, icanon->buffer, 3);
		if (icanon->buffer[0] == 4)
			ret = ft_ctrl_d(shell_c, icanon);
		else if (icanon->buffer[0] >= 32 && icanon->buffer[0] <= 126)
			icanon->line_i = ft_insert_char(icanon);
		else if (icanon->buffer[0] == 127 && icanon->column > 0)
			ft_backspace(icanon);
		else if (icanon->buffer[0] == '\f')
			ft_ctrl_l(shell_c, icanon->line);
		else if (icanon->buffer[0] == '\n')
			ret = ft_putchar('\n') * 0;
		else if (icanon->buffer[0] == 27 && icanon->buffer[1] == 91)
			ft_escape_code(shell_c, icanon);
		else
			tputs(bell, 1, ft_putchar);
		if (icanon->buffer[0] != '\n')
			ft_rewrite_line(icanon);
	}
	icanon->line[icanon->line_i] = '\0';
	return (0);
}
