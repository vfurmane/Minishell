/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarrdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 14:12:42 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/26 14:09:54 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	**ft_strarrdup(char **arr)
{
	int		i;
	char	**result;

	i = 0;
	result = malloc(sizeof(*result) * (ft_arrlen(arr) + 1));
	if (result == NULL)
		return (NULL);
	while (arr[i])
	{
		result[i] = ft_strdup(arr[i]);
		i++;
	}
	result[i] = NULL;
	return (result);
}
