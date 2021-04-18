/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcidup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 15:45:55 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/18 15:46:21 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char *ft_strcidup(const char *str, int chr)
{
	int str_len;
	char *new_str;
	char *first_chr;

	first_chr = ft_strchr(str, chr);
	str_len = first_chr - str + 1;
	if (!(new_str = malloc(sizeof(*new_str) * (str_len + 1))))
		return (NULL);
	new_str = ft_memcpy(new_str, str, sizeof(*new_str) * str_len);
	new_str[str_len] = '\0';
	return (new_str);
}
