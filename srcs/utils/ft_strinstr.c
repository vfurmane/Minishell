/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 13:39:42 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/28 15:51:33 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strinstr_last(const char *str, const char *sep)
{
	int i;
	int j;

	i = 0;
	j = -1;
	while (str[i])
	{
		if (ft_strchr(sep, str[i]) != NULL)
			j = i;
		i++;
	}
	if (j != -1)
		return ((char *)&str[j]);
	return (NULL);
}

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
