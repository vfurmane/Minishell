/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 17:18:45 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/04 10:30:32 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_stderr_message(const char *str1, const char *str2, const char *str3,
		int ret)
{
	write(2, "minishell: ", 11);
	write(2, str1, ft_strlen(str1));
	if (str2 != NULL)
	{
		write(2, str2, ft_strlen(str2));
		if (str3 != NULL)
			write(2, str3, ft_strlen(str3));
	}
	write(2, "\n", 1);
	return (ret);
}
