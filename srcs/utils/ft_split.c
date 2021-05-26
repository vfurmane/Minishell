/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 13:31:58 by earnaud           #+#    #+#             */
/*   Updated: 2021/05/26 14:07:26 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_words(const char *str, char sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == sep)
			i++;
		if (str[i])
			count++;
		else
			break ;
		while (str[i] && str[i] != sep)
			i++;
	}
	return (count);
}

char	**ft_split(const char *str, char sep)
{
	int		i;
	int		j;
	char	**arr;

	i = 0;
	j = 0;
	arr = malloc((ft_count_words(str, sep) + 1) * sizeof(*arr));
	if (arr == NULL)
		return (NULL);
	while (str[i])
	{
		while (str[i] == sep)
			i++;
		if (str[i])
			arr[j++] = ft_strcdup(&str[i], sep);
		else
			break ;
		while (str[i] && str[i] != sep)
			i++;
	}
	arr[j] = NULL;
	return (arr);
}
