/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:09:52 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/14 21:18:05 by vfurmane         ###   ########.fr       */
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
	buffer_fix = ft_fix_openfiles(shell_c, buffer, cmd, error);
	cmd->next = NULL;
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

void	free_all_cmd(t_cmd *cmd)
{
	t_cmd *temp;
	while (cmd)
	{
		temp = cmd->next;
		free(cmd->str);
		free(cmd);
		cmd = temp;
	}
}

int ft_init_args_tree(t_config *shell_c, char *const buffer)
{
	int i;
	char *str;
	t_cmd *cmd;
	int bracket;
	int errorfile;

	i = 0;
	errorfile = 0;
	bracket = 0;
	cmd = NULL;
	str = buffer;

	while (str[i])
	{
		ft_cmdadd_back(&cmd, ft_new_cmd(shell_c, &str[i], &errorfile));
		if (errorfile)
			return (errorfile); //free all cmd before
		if (cmd == NULL)
			return (0);

		if (str[i] == '\0')
			break;
		while (str[i] && !ft_strchr("|;", str[i]))
			i++;
		if (str[i] == ';')
			i++;
		if (str[i] == '|')
		{
			ft_cmdlast(cmd)->separator = PIPE; //that's not usefull
			while (str[i] == '|')
				i++;
		}
	}
	if (cmd == NULL)
		return (0);
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

int ft_prompt(t_config *shell_c, int pipefd[2])
{
	int				ret;
	struct termios	termios_c;
	t_icanon		icanon;
	
	(void)(pipefd);
	tcgetattr(0, &termios_c);
	termios_c.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, 0, &termios_c);
	icanon.line_i = 0;
	icanon.column = 0;
	ft_display_prompt(shell_c->prompt);
	ft_lstadd_front(&shell_c->history, ft_new_history_line());
	icanon.line = shell_c->history->content;
	if (shell_c->history->next)
		shell_c->history->next->previous = shell_c->history;
	ft_read_icanon(shell_c, &icanon);
	tcsetattr(0, 0, &shell_c->termios_backup);
	signal(SIGINT, SIG_IGN);
	if (icanon.line[0] == '\0')
		exit(S_SIGIGN);
	ft_write_pipe(ADD_HISTORY, icanon.line, NULL, shell_c->fd[1]);
	ret = ft_init_args_tree(shell_c, icanon.line);
	return (ret);
}
