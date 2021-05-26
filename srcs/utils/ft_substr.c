/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:13:27 by earnaud           #+#    #+#             */
/*   Updated: 2021/05/26 14:18:38 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	k;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	k = ft_strlen(&s[start]);
	if (k > len)
		k = len;
	result = malloc((k + 1) * sizeof(char));
	if (result != NULL)
		ft_strlcpy(result, &s[start], k + 1);
	return (result);
}
