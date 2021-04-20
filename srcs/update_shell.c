/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_shell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 15:14:23 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/20 11:29:23 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_read_whole_fd(int fd)
{
	int ret;
	char *str;
	char *tmp_str;
	char buffer[BUFSIZ + 1];

	ret = 1;
	str = ft_calloc(sizeof(*str), 1);
	while (ret > 0)
	{
		ret = read(fd, buffer, BUFSIZ);
		if (ret == -1)
			return (NULL);
		buffer[ret] = '\0';
		tmp_str = ft_strjoin(str, buffer);
		if (tmp_str == NULL)
			return (NULL);
		free(str);
		str = tmp_str;
		if (buffer[ret - 1] == '\0')
			return (str);
	}
	return (str);
}

int ft_route_updater(t_config *shell_c, char *str)
{
	int i;
	int ret;
	char key[4];
	char *value;

	i = 0;
	while (str[i] && str[i] != 31)
		i++;
	if (str[i] == '\0')
		return (-1);
	ft_strlcpy(key, str, ++i);
	value = ft_strcdup(&str[i], 30);
	ret = -1;
	if (ft_strcmp(ADD_ENV, key) == 0)
		ret = ft_add_env(shell_c, value);
	else if (ft_strcmp(DEL_ENV, key) == 0)
		ret = ft_del_env(shell_c, value);
	else if (ft_strcmp(EXIT_SHELL, key) == 0)
		shell_c->quit = 1;
	else if (ft_strcmp(CD_CHANGE, key) == 0)
		ret = chdir(value);
	if (ret == -1)
		return (ret);
	while (str[i] && str[i] != 30)
		i++;
	return (i + 1);
}

// Protect return in main
int ft_update_shell(t_config *shell_c)
{
	int i;
	int ret;
	char *str;

	write(shell_c->fd[1], "\0", 1);
	str = ft_read_whole_fd(shell_c->fd[0]);
	if (str == NULL)
		return (-1);
	i = 0;
	while (str[i])
	{
		ret = ft_route_updater(shell_c, &str[i]);
		if (ret == -1)
			return (-1);
		i += ret;
	}
	return (0);
}
