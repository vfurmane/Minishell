/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 21:33:08 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/26 14:08:42 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_words(const char *str, char *sep)
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

static char	*ft_strcdup(const char *str, char *sep)
{
	int		i;
	int		str_len;
	char	*new_str;

	str_len = 0;
	while (str[str_len] && str[str_len] != sep)
		str_len++;
	new_str = malloc(sizeof(*new_str) * (str_len + 1));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != sep)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[str_len] = '\0';
	return (new_str);
}

char	**ft_splitstr(const char *str, char *sep)
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
		while (ft_strchr(sep, str[i]) == NULL)
			i++;
		if (str[i])
			arr[j++] = ft_strdupstr(&str[i], sep);
		else
			break ;
		while (str[i] && str[i] != sep)
			i++;
	}
	arr[j] = NULL;
	return (arr);
}
