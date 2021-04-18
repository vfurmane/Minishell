/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_malloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:32:18 by earnaud           #+#    #+#             */
/*   Updated: 2021/04/18 13:09:41 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_fd_to_str(int fd, char **str)
{
	int ret;
	int len;
	char *tmp;
	char buffer[ARG_MAX];

	ret = 1;
	len = 0;
	*str = NULL;
	ft_memset(buffer, 0, ARG_MAX);
	while (ret)
	{
		ret = read(fd, buffer, ARG_MAX);
		if (ret == -1)
			return (-1);
		tmp = malloc(len + ret);
		//* sizeof(char)
		//check the malloc
		ft_memcpy(tmp, str, len);
		ft_memcpy(tmp + len, buffer, ret);
		free(*str);
		len += ret;
		*str = tmp;
		if (!(buffer[ret]) && !(buffer[ret - 1]))
			return (len - 1);
		//if ((size_t)ret > ft_strlen(buffer))
		//	return (len - 1);
	}
	return (len - 1);
}

/*void ft_update_env(int pipefd[2], char ***environment)
{
	int i;
	int j;
	int ret;
	char *str;
	char **new_env;

	ret = ft_fd_to_str(pipefd[0], &str);
	if (ret == -1) // The return
		return;
	i = 0;
	j = 0;
	while (i < ret)
	{
		while (str[i])
			i++;
		i++;
		j++;
	}
	new_env = malloc(sizeof(*new_env) * j);
	i = 0;
	j = 0;
	while (i < ret)
	{
		new_env[j] = malloc(((ft_strlen(str + i) + 1) * sizeof(**new_env)));
		ft_strlcpy(new_env[j++], str + i, ft_strlen(str + i) + 1);
		while (str[i])
			i++;
		i++;
	}
	new_env[j] = 0;
	free(*environment);
	*environment = new_env;
}*/
