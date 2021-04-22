/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   icanon_put.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 09:57:56 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/22 10:34:06 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_insert_char(t_icanon *icanon)
{
	int	i;

	i = ft_strlen(&icanon->line[icanon->column]) + 1;
	while (--i >= 0)
		icanon->line[icanon->column + i + 1] = icanon->line[icanon->column + i];
	icanon->line[(icanon->column)++] = icanon->buffer[0];
	ft_putchar(icanon->buffer[0]);
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

int	ft_rewrite_line(t_icanon *icanon, int move_cursor)
{
	int	i;

	i = icanon->column;
	tputs(save_cursor, 1, ft_putchar);
	while (i < icanon->line_i)
		ft_putchar(icanon->line[i++]);
	if (!move_cursor)
		tputs(restore_cursor, 1, ft_putchar);
	return (0);
}
