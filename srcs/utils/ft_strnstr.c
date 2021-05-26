/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 17:21:09 by earnaud           #+#    #+#             */
/*   Updated: 2021/05/26 14:18:10 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	little_len;

	i = 0;
	little_len = ft_strlen(little);
	if (!*little)
		return ((char *)big);
	while (i <= len && big[i])
	{
		j = 0;
		while (j <= little_len && i + j < len)
		{
			if (little[j] == big[i + j])
			{
				if (j == little_len - 1)
					return ((char *)(big + i));
				j++;
			}
			else
				break ;
		}
		i++;
	}
	return (0);
}
