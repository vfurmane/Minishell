/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 16:49:20 by earnaud           #+#    #+#             */
/*   Updated: 2021/05/28 15:30:25 by vfurmane         ###   ########.fr       */
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
		if (shell_c->envp == NULL || envp_elm == NULL)
			return (-1);
		envp_elm->next = NULL;
		envp_elm->key = ft_strcdup(envp[i], '=');
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		if (envp[i][j] == '\0' || envp[i][j + 1] == '\0')
			return (-1);
		j++;
		envp_elm->value = ft_strdup(&envp[i++][j]);
		ft_lstadd_back(&shell_c->envp_list, envp_elm);
	}
	ft_update_env(shell_c);
	return (0);
}

char	*ft_getenv(t_kvpair *envp_list, const char *name)
{
	while (envp_list)
	{
		if (ft_strcmp(name, envp_list->key) == 0)
			return (envp_list->value);
		envp_list = envp_list->next;
	}
	return (0);
}

static int	ft_get_var_name(char **env_name, const char *dollar_str)
{
	int		i;

	i = 0;
	if (dollar_str[0] == '?')
		i++;
	else
		while (ft_isalpha(dollar_str[i])
			|| (ft_isdigit(dollar_str[i] && i > 0)) || dollar_str[i] == '_')
			i++;
	*env_name = malloc(sizeof(*env_name) * (i + 1));
	if (*env_name == NULL)
		return (-1);
	ft_strlcpy(*env_name, dollar_str, i + 1);
	return (i);
}

int	ft_replace_dollar(t_config *shell_c, char **dest,
		const char *dollar_str)
{
	int		ret;
	char	*env;
	char	*env_name;

	ret = ft_get_var_name(&env_name, dollar_str);
	if (ret == -1)
		return (-1);
	if (env_name[0] == '\0')
		env = "$";
	else if (ft_strcmp(env_name, "?") == 0)
		env = ft_static_itoa(shell_c->exit_code);
	else
		env = ft_getenv(shell_c->envp_list, env_name);
	free(env_name);
	if (env == NULL)
		env = "";
	if (dest)
		*dest = env;
	return (ret);
}
