/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 12:12:43 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/27 13:51:40 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

int	ft_insert_char(t_icanon *icanon)
{
	int	i;
	int	buffer_i;

	buffer_i = 0;
	while (icanon->buffer[buffer_i]
		&& icanon->column + icanon->start_column < columns - 1)
	{
		i = ft_strlen(&icanon->line[icanon->column]) + 1;
		while (--i >= 0)
			icanon->line[icanon->column + i + 1] = icanon->line[icanon->column
				+ i];
		icanon->line[(icanon->column)++] = icanon->buffer[buffer_i];
		ft_putchar(icanon->buffer[buffer_i]);
		buffer_i++;
	}
	return (ft_strlen(icanon->line));
}

int	ft_delete_char(char *str, int column)
{
	int	i;
	int	len;

	len = ft_strlen(&str[column]) + 1;
	column--;
	i = -1;
	while (++i < len)
		str[column + i] = str[column + i + 1];
	return (ft_strlen(str));
}

int	ft_backspace(t_icanon *icanon)
{
	icanon->line_i = ft_delete_char(icanon->line, (icanon->column)--);
	tputs(tgoto(cursor_left, 0, 0), 1, ft_putchar);
	tputs(clr_eol, 1, ft_putchar);
	return (0);
}

int	ft_rewrite_line(t_icanon *icanon, int move_cursor)
{
	int	i;

	i = icanon->column;
	tputs(clr_eol, 1, ft_putchar);
	tputs(save_cursor, 1, ft_putchar);
	while (i < icanon->line_i)
		ft_putchar(icanon->line[i++]);
	if (!move_cursor)
		tputs(restore_cursor, 1, ft_putchar);
	return (0);
}
