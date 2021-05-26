/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarrstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 11:28:30 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/26 14:10:07 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strarrstr(const char **arr, const char *str, int *index)
{
	*index = 0;
	while (arr[*index])
	{
		if (ft_strcmp(str, arr[*index]) == 0)
			return (((char **)arr)[*index]);
		(*index)++;
	}
	*index = -1;
	return (NULL);
}
