/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 16:49:20 by earnaud           #+#    #+#             */
/*   Updated: 2021/05/11 10:18:31 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_getenv(t_kvpair *envp_list, const char *name)
{
	while (envp_list)
	{
		if (ft_strcmp(name, envp_list->key) == 0)
			return (envp_list->value);
		envp_list = envp_list->next;
	}
	return (0);
}

char *ft_replace_with_env(t_config *shell_c, const char *str, int *str_i)
{
	int i;
	char *env;
	char *env_name;

	i = 0;
	if (str[0] == '?')
		i++;
	else
		while (ft_isalpha(str[i]) || (ft_isdigit(str[i] && i > 0)) ||
			str[i] == '_')
			i++;
	*str_i += i;
	env_name = malloc(sizeof(*env) * (i + 1));
	if (env_name == NULL)
		return (NULL);
	ft_strlcpy(env_name, str, i + 1);
	if (ft_strcmp(env_name, "?") == 0)
		env = ft_static_itoa(shell_c->exit_code);
	else
		env = ft_getenv(shell_c->envp_list, env_name);
	free(env_name);
	if (env == NULL)
		env = "";
	return (env);
}
