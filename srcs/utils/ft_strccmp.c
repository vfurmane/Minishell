/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strccmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 17:26:10 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/18 10:23:37 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_strccmp(const char *str1, const char *str2, int chr)
{
	size_t	i;

	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i] || str1[i] == chr || str2[i] == chr)
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}
