/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 13:10:20 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/18 13:11:30 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_lstsize(void *lst)
{
	int	len;

	if (lst == NULL)
		return (0);
	len = 1;
	while ((lst = ((t_next*)lst)->next))
		len++;
	return (len);
}
