/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_malloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:32:18 by earnaud           #+#    #+#             */
/*   Updated: 2021/04/07 16:42:54 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t ft_strstrlen(char **str)
{
	size_t i;

	i = 0;
	if (str)
	{
		while (str[i])
			i++;
	}
	return (i);
}

int	ft_fd_to_str(int fd, char **str)
{
	int		ret;
	int		len;
	char	*tmp;
	char	buffer[ARG_MAX + 1];

	ret = 1;
	*str = NULL;
	while (ret)
	{
		ret = read(fd, buffer, ARG_MAX);
		if (ret == -1)
			return (-1);
		tmp = malloc(len + ret);
		ft_memcpy(tmp, str, len);
		ft_memcpy(tmp + len, buffer, ret);
		free(*str);
		len += ret;
		*str = tmp;
	}
	return (len);
}

void	ft_update_env()
{
	int		i;
	int		j;
	int		ret;
	char	*str;
	char	**new_env;
	
	ret = ft_fd_to_str(pip[0], &str);
	if (ret == -1) // The return
		return ;
	i = 0;
	j = 0;
	while (i < ret)
	{
		new_env[j] = malloc((ft_strlen(str + i + 1 ) * sizeof(**new_env)));
		ft_strcpy(new_env[j++], str + i);
		while (str[i])
			i++;
		i++;
	}
}

char **ft_env_malloc(char **envp)
{
	char **result;
	int i;

	i = 0;
	result = malloc(sizeof(char *) * (ft_strstrlen(envp) + 1));
	if (!result)
	return (NULL);
	while (envp[i])
	{
		result[i] = ft_strdup((const char *)envp[i]);
		i++;
	}
	result[i] = NULL;
	return (result);
}