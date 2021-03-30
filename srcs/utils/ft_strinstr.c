/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 13:39:42 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/31 13:42:22 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strinstr(const char *str, const char *sep)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(sep, str[i]) != NULL)
			return ((char*)&str[i]);
		i++;
	}
	return (NULL);
}
