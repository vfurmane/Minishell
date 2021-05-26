/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 12:31:47 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/26 12:31:56 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_add_history(t_config *shell_c, char *str)
{
	t_dlist	*elm;

	elm = malloc(sizeof(*elm));
	if (elm == NULL)
		return (-1);
	elm->next = NULL;
	elm->previous = NULL;
	elm->content = ft_strdup(str);
	ft_lstadd_front(&shell_c->history, elm);
	if (shell_c->history->next)
		shell_c->history->next->previous = shell_c->history;
	return (0);
}
