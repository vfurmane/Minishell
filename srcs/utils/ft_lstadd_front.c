/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 11:30:44 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/21 11:35:56 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_lstadd_front(void *lst, void *new)
{
	((t_next*)new)->next = *(t_next**)lst;
	*(t_next**)lst = new;
	return (new);
}
