/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 12:44:06 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/26 13:53:21 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_lstadd_back(void *lst, void *new)
{
	if (*(t_next **)lst == NULL)
		*(t_next **)lst = new;
	else
		((t_next *)ft_lstlast(*(t_next **)lst))->next = new;
	return (new);
}
