/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 14:36:19 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/23 14:37:27 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parse_envp(char **envp, t_config *shell_c)
{
	int			i;
	int			j;
	t_kvpair	*envp_elm;

	i = 0;
	shell_c->envp = ft_calloc(sizeof(*shell_c->envp), 1);
	shell_c->envp_list = NULL;
	while (envp[i])
	{
		envp_elm = malloc(sizeof(*envp_elm));
		envp_elm->next = NULL;
		envp_elm->key = ft_strcdup(envp[i], '=');
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		if (envp[i][j++] == '\0')
			return (-1);
		envp_elm->value = ft_strdup(&envp[i][j]);
		ft_lstadd_back(&shell_c->envp_list, envp_elm);
		i++;
	}
	ft_update_env(shell_c);
	return (0);
}
