/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 16:12:16 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/18 17:09:33 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_update_env(t_config *shell_c)
{
	int			i;
	t_kvpair	*envp_elm;

	envp_elm = shell_c->envp_list;
	i = 0;
	while (shell_c->envp[i])
		free(shell_c->envp[i++]);
	free(shell_c->envp);
	shell_c->envp = malloc(sizeof(*shell_c->envp) *
			(ft_lstsize(shell_c->envp_list) + 1));
	i = 0;
	while (envp_elm)
	{
		shell_c->envp[i++] = ft_strjoin(envp_elm->key, envp_elm->value);
		envp_elm = envp_elm->next;
	}
	shell_c->envp[i] = NULL;
	return (0);
}

void	*ft_del_env_elm(t_config *shell_c, t_kvpair *elm, t_kvpair *previous)
{
	t_kvpair	*next;

	if (previous != NULL)
		previous->next = elm->next;
	else
		shell_c->envp_list = elm->next;
	free(elm->key);
	free(elm->value);
	next = elm->next;
	free(elm);
	return (next);
}

int		ft_del_env(t_config *shell_c, char *str)
{
	char		*tmp;
	t_kvpair	*previous;
	t_kvpair	*envp_elm;

	previous = NULL;
	envp_elm = shell_c->envp_list;
	tmp = ft_strjoin(str, "=");
	while (envp_elm)
	{
		if (ft_strcmp(tmp, envp_elm->key) == 0)
			envp_elm = ft_del_env_elm(shell_c, envp_elm, previous);
		else
		{
			previous = envp_elm;
			envp_elm = envp_elm->next;
		}
	}
	ft_update_env(shell_c);
	free(tmp);
	return (0);
}

int		ft_check_duplicate_env(t_kvpair *envp_list, const char *str, int i)
{
	t_kvpair	*envp_elm;

	envp_elm = envp_list;
	while (envp_elm)
	{
		if (ft_strccmp(str, envp_elm->key, '=') == 0)
		{
			free(envp_elm->value);
			envp_elm->value = ft_strdup(&str[i]);
			return (1);
		}
		envp_elm = envp_elm->next;
	}
	return (0);
}

int		ft_add_env(t_config *shell_c, const char *str)
{
	int			j;
	t_kvpair	*envp_elm;

	j = 0;
	while (str[j] && str[j] != '=')
		j++;
	if (str[j] == '=')
		j++;
	if (!ft_check_duplicate_env(shell_c->envp_list, str, j))
	{
		envp_elm = malloc(sizeof(*envp_elm));
		envp_elm->next = NULL;
		envp_elm->key = ft_strcidup(str, '=');
		envp_elm->value = ft_strdup(&str[j]);
		ft_lstadd_back(&shell_c->envp_list, envp_elm);
	}
	ft_update_env(shell_c);
	return (0);
}
