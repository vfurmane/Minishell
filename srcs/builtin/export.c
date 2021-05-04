/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 12:08:23 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/04 10:53:00 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	ft_print_exp_list(int fd, t_kvpair *envp_list)
{
	int			key_len;
	t_kvpair	*envp_elm;

	envp_elm = envp_list;
	while (envp_elm)
	{
		write(fd, "declare -x ", 12);
		key_len = ft_strlen(envp_elm->key);
		write(fd, envp_elm->key, key_len);
		if (envp_elm->value != NULL)
		{
			write(fd, "=\"", 2);
			write(fd, envp_elm->value, ft_strlen(envp_elm->value));
			write(fd, "\"", 1);
		}
		write(fd, "\n", 1);
		envp_elm = envp_elm->next;
	}
	return (0);
}

static int	ft_is_valid_identifier(const char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=' && (ft_isalpha(arg[i]) ||
				(ft_isdigit(arg[i]) && i > 0) || arg[i] == '_'))
		i++;
	return ((arg[i] == '\0' || arg[i] == '=') && i > 0);
}

int			ft_export(char **args, int fd, t_config *shell_c)
{
	int	i;
	
	if (args[0] == NULL)
		return (ft_print_exp_list(fd, shell_c->envp_list));
	i = 0;
	while (args[i])
	{
		if (!ft_is_valid_identifier(args[i]))
		{
			ft_stderr_message("export: `", args[i],
					"': not a valid identifier", 1);
		}
		else
			ft_write_pipe(ADD_ENV, args[i], NULL, shell_c->fd[1]);
		i++;
	}
	return (0);
}
