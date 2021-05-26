/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 09:38:43 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/26 11:26:24 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_add_characters(t_config *shell_c, t_cmd_arg *arg,
		const char *cmd)
{
	int		i;
	int		env_len;
	char	*env_variable;

	i = 0;
	if (cmd[0] == '$' && arg->quote != '\'')
	{
		i = ft_replace_dollar(shell_c, &env_variable, &cmd[1]);
		env_len = ft_strlen(env_variable);
		ft_strcpy(&arg->str[arg->i], env_variable);
		arg->i += env_len;
	}
	else
	{
		arg->str[arg->i] = cmd[0];
		arg->i++;
	}
	return (i + 1);
}

char	*ft_cmd_argdup(t_config *shell_c, const char *cmd)
{
	int			i;
	t_cmd_arg	arg;

	ft_bzero(&arg, sizeof(arg));
	arg.str = ft_calloc((ft_arglen(shell_c, cmd) + 1), sizeof(*arg.str));
	if (arg.str == NULL)
		return (NULL);
	i = 0;
	while (cmd[i] && (cmd[i] != ' ' || arg.quote != '\0'))
	{
		if (ft_set_backslash(&arg, cmd[i], &i))
			continue ;
		if (arg.backslash)
			arg.str[arg.i++] = cmd[i++];
		else if (cmd[i] == '\'' || cmd[i] == '"')
			arg.quote = ft_set_quote(&arg, cmd[i++]);
		else
			i += ft_add_characters(shell_c, &arg, &cmd[i]);
		arg.backslash = 0;
	}
	if (arg.quote != '\0')
		return ((void *)(uintptr_t)ft_stderr_message("unterminated quote",
			NULL, NULL, 0));
	return (arg.str);
}

static int	ft_count_args(const char *cmd)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		ft_skip_spaces(cmd, &i);
		if (cmd[i] == '\0')
			break ;
		ft_skip_cmd_arg(cmd, &i);
		j++;
	}
	return (j);
}

char	**ft_split_cmd(t_config *shell_c, const char *cmd)
{
	int		i;
	int		j;
	char	**argv;

	argv = malloc(sizeof(*argv) * (ft_count_args(cmd) + 1));
	if (argv == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (cmd[i])
	{
		ft_skip_spaces(cmd, &i);
		if (cmd[i] == '\0')
			break ;
		argv[j] = ft_cmd_argdup(shell_c, &cmd[i]);
		if (argv[j] == NULL)
			return (NULL);
		ft_skip_cmd_arg(cmd, &i);
		j++;
	}
	argv[j] = NULL;
	return (argv);
}
