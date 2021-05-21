/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:09:52 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/21 14:19:13 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_separator ft_set_separator(const char *str)
{
	if (str[0] == ';')
		return (EOCMD);
	//else if (str[0] == '<') // not useful
	//	return (REDIR_LEFT); // not useful
	//else if (str[0] == '>') // not useful
	//	if (str[1] == '>') // not useful
	//		return (REDIR_APPEND); // not useful
	//	else 						// not useful
	//		return (REDIR_RIGHT); // not useful
	else if (str[0] == '|')
		return (PIPE);
	else
		return (EOCMD);
}

t_cmd *ft_new_cmd(t_config *shell_c, char *const buffer, int *error)
{
	t_cmd	*cmd;
	char	*separator;
	char	*buffer_fix;

	cmd = malloc(sizeof(*cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->next = NULL;
	cmd->file = 0;
	cmd->file_from = 0;
	cmd->file_to = 0;
	cmd->from_to = 0;
	cmd->fd[0] = 0;
	cmd->fd[1] = 0;
	buffer_fix = ft_fix_openfiles(shell_c, buffer, cmd, error);
	separator = ft_strinstr(buffer, ";|");
	if (separator == NULL)
		separator = &buffer[ft_strlen(buffer)];
	if (buffer_fix)
		cmd->str = buffer_fix;
	else if (!*error)
		cmd->str = ft_strndup(buffer, separator - buffer);
	else
		return (NULL);
	cmd->separator = ft_set_separator(separator);
	return (cmd);
}

t_cmd *ft_cmdlast(t_cmd *cmd)
{
	if (!(cmd))
		return (0);
	while (cmd->next)
		cmd = cmd->next;
	return (cmd);
}

void ft_cmdadd_back(t_cmd **acmd, t_cmd *new)
{
	if (!(*acmd))
	{
		*acmd = new;
		return;
	}
	ft_cmdlast(*acmd)->next = new;
}

int ft_in_str_where(char *str, char c, int last)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			if (last)
				while (str[i] == c)
					i++;
			return (i);
		}
		i++;
	}
	return (0);
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

static char	*ft_skip_spaces(const char *cmd, int *i)
{
	while (cmd[*i] == ' ')
		(*i)++;
	return ((char*)(&cmd[*i]));
}

static char *ft_skip_cmd(const char *cmd, int *i)
{
	int			j;
	t_cmd_arg	arg;

	ft_bzero(&arg, sizeof(arg));
	j = 0;
	while (cmd[*i] && ((cmd[*i] != ';' && cmd[*i] != '|') || arg.quote != '\0'))
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
	(*i)++;
	return ((char*)&cmd[*i]);
}

int ft_init_args_tree(t_config *shell_c, char *const buffer)
{
	int		i;
	char	*str;
	t_cmd	*cmd;
	int		bracket;
	int		errorfile;

	i = 0;
	errorfile = 0;
	bracket = 0;
	cmd = NULL;
	str = buffer;
	while (str[i])
	{
		ft_cmdadd_back(&cmd, ft_new_cmd(shell_c, &str[i], &errorfile));
		if (errorfile)
		{
			free_all_cmd(cmd);
			return (errorfile);
		}
		if (cmd == NULL)
		{
			free_all_cmd(cmd);
			return (0);
		}
		if (str[i] == '\0')
			break ;
		ft_skip_cmd(str, &i);
		ft_skip_spaces(str, &i);
	}
	// why i ?
	i = ft_recursiv_command(cmd, shell_c, STDIN_FILENO, dup(STDOUT_FILENO));
	free_all_cmd(cmd);
	return (i);
}

int	ft_display_prompt(char *prompt)
{
	return (write(1, prompt, ft_strlen(prompt)));
}

t_dlist	*ft_new_history_line(void)
{
	t_dlist	*elm;

	elm = malloc(sizeof(*elm));
	if (elm == NULL)
		return (NULL);
	elm->next = NULL;
	elm->previous = NULL;
	elm->content = ft_calloc(sizeof(elm), ARG_MAX + 1);
	return (elm);
}

static void	ft_sigint_prompt(int code)
{
	if (code == SIGINT)
		exit(S_SIGINT_PROMPT);
}

int ft_prompt(t_config *shell_c)
{
	int				ret;
	struct termios	termios_c;
	t_icanon		icanon;

	signal(SIGINT, ft_sigint_prompt);
	tcgetattr(0, &termios_c);
	termios_c.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, 0, &termios_c);
	icanon.line_i = 0;
	icanon.column = 0;
	ft_display_prompt(shell_c->prompt);
	ft_lstadd_front(&shell_c->history, ft_new_history_line());
	icanon.line = shell_c->history->content;
	if (shell_c->history->next != NULL)
		shell_c->history->next->previous = shell_c->history;
	ft_read_icanon(shell_c, &icanon);
	tcsetattr(0, 0, &shell_c->termios_backup);
	signal(SIGQUIT, SIG_DFL);
	if (icanon.line[0] == '\0')
		return (S_SIGIGN);
	ft_write_pipe(ADD_HISTORY, icanon.line, NULL, shell_c->fd[1]);
	ret = ft_init_args_tree(shell_c, icanon.line);
	return (ret);
}
