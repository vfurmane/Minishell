/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 09:38:43 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/14 11:51:09 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_skip_spaces(const char *cmd, int *i)
{
	while (cmd[*i] == ' ')
		(*i)++;
	return ((char*)(&cmd[*i]));
}

/* ===== DELETE ===== */

typedef struct	s_cmd_arg
{
	int			i;
	int			backslash;
	char		*str;
	char		quote;
}				t_cmd_arg;

/* ===== DELETE ===== */

static int	ft_replace_dollar(t_config *shell_c, char **dest,
		const char *dollar_str)
{
	int i;
	char *env;
	char *env_name;

	i = 0;
	if (dollar_str[0] == '?')
		i++;
	else
		while (ft_isalpha(dollar_str[i]) ||
				(ft_isdigit(dollar_str[i] && i > 0)) ||	dollar_str[i] == '_')
			i++;
	env_name = malloc(sizeof(*env) * (i + 1));
	if (env_name == NULL)
		return (-1);
	ft_strlcpy(env_name, dollar_str, i + 1);
	if (ft_strcmp(env_name, "?") == 0)
		env = ft_static_itoa(shell_c->exit_code);
	else
		env = ft_getenv(shell_c->envp_list, env_name);
	free(env_name);
	if (env == NULL)
		env = "";
	if (dest)
		*dest = env;
	return (i);
}

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

static char	ft_set_quote(t_cmd_arg *arg, char chr)
{
	if (arg->quote != '\0' && arg->quote == chr)
		arg->quote = '\0';
	else if (arg->quote == '\0' && (chr == '"' || chr == '\''))
		arg->quote = chr;
	else
	{
		if (arg->str != NULL)
			arg->str[arg->i] = chr;
		arg->i++;
	}
	return (arg->quote);
}

static char	*ft_skip_cmd_arg(const char *cmd, int *i)
{
	t_cmd_arg	arg;

	arg.i = 0;
	arg.backslash = 0;
	arg.quote = 0;
	arg.str = NULL;
	while (cmd[*i] && (cmd[*i] != ' ' || arg.quote != '\0'))
	{
		if (!arg.backslash && cmd[*i] == '\\')
		{
			arg.backslash = cmd[(*i)++] == '\\';
			continue ;
		}
		if (arg.backslash)
			(*i)++;
		else if (cmd[*i] == '\'' || cmd[*i] == '"')
			arg.quote = ft_set_quote(&arg, cmd[(*i)++]);
		else
			(*i)++;
		arg.backslash = 0;
	}
	return ((char*)&cmd[*i]);
}

static int	ft_arglen(t_config *shell_c, const char *cmd)
{
	int			i;
	t_cmd_arg	arg;

	i = 0;
	arg.i = 0;
	arg.backslash = 0;
	arg.quote = 0;
	arg.str = NULL;
	while (cmd[i] && (cmd[i] != ' ' || arg.quote != '\0'))
	{
		if (!arg.backslash && cmd[i] == '\\')
		{
			arg.backslash = cmd[i++] == '\\';
			continue ;
		}
		if (arg.backslash)
			i++;
		else if (cmd[i] == '\'' || cmd[i] == '"')
			arg.quote = ft_set_quote(&arg, cmd[i++]);
		else if (cmd[i] == '$')
			i += ft_replace_dollar(shell_c, NULL, &cmd[i + 1]);
		else
			i++;
		arg.backslash = 0;
	}
	return (i);
}

static char	*ft_cmd_argdup(t_config *shell_c, const char *cmd)
{
	int			i;
	t_cmd_arg	arg;

	arg.str = ft_calloc(sizeof(*arg.str), (ft_arglen(shell_c, cmd) + 1));
	if (arg.str == NULL)
		return (NULL);
	arg.i = 0;
	arg.quote = '\0';
	arg.backslash = 0;
	i = 0;
	while (cmd[i] && (cmd[i] != ' ' || arg.quote != '\0'))
	{
		if (!arg.backslash && cmd[i] == '\\')
		{
			arg.backslash = cmd[i++] == '\\';
			continue ;
		}
		if (arg.backslash)
			arg.str[arg.i++] = cmd[i++];
		else if (cmd[i] == '\'' || cmd[i] == '"')
			arg.quote = ft_set_quote(&arg, cmd[i++]);
		else
			i += ft_add_characters(shell_c, &arg, &cmd[i]);
		arg.backslash = 0;
	}
	if (arg.quote != '\0')
		return ((void*)(uintptr_t)ft_stderr_message("unterminated quote", NULL, NULL, 0));
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

char		**ft_split_cmd(t_config *shell_c, const char *cmd)
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
		ft_skip_spaces(cmd, &i); //
		if (cmd[i] == '\0')
			break ;
		argv[j] = ft_cmd_argdup(shell_c, &cmd[i]);
		if (argv[j] == NULL)
			return (NULL);
		ft_skip_cmd_arg(cmd, &i); //
		j++;
	}
	argv[j] = NULL;
	return (argv);
}
