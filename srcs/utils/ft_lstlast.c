/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 12:45:25 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/26 13:53:48 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_lstlast(void *lst)
{
	if (lst == NULL)
		return (NULL);
	while (((t_next *)lst)->next != NULL)
		lst = ((t_next *)lst)->next;
	return (lst);
}
