/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 11:57:40 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/23 12:12:24 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCAPS_H
# define TERMCAPS_H

#include "minishell.h"

typedef struct s_icanon	t_icanon;
typedef struct s_config	t_config;

int	ft_ctrl_d(t_config *shell_c, t_icanon *icanon);
int	ft_ctrl_l(t_config *shell_c, char *line);

int	ft_escape_code(t_config *shell_c, t_icanon *icanon);

int	ft_backspace(t_icanon *icanon);

int	ft_read_icanon(t_config *shell_c, t_icanon *icanon);

#endif
