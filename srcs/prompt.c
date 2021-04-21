/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:09:52 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/21 16:04:08 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_separator ft_set_separator(const char *str)
{
	if (str[0] == ';')
		return (EOCMD);
	else if (str[0] == '<')
		return (REDIR_LEFT);
	else if (str[0] == '>')
		if (str[1] == '>')
			return (REDIR_APPEND);
		else
			return (REDIR_RIGHT);
	else if (str[0] == '|')
		return (PIPE);
	else
		return (EOCMD);
}

t_cmd *ft_new_cmd(char *const buffer)
{
	t_cmd *cmd;
	char *separator;

	cmd = malloc(sizeof(*cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->next = NULL;
	separator = ft_strinstr(buffer, ";|<>");
	if (separator == NULL)
		separator = &buffer[ft_strlen(buffer)];
	cmd->str = ft_strndup(buffer, separator - buffer);
	if (cmd->str == NULL)
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
	new->next = 0;
}

int ft_init_args_tree(char *const buffer, t_config *shell_c, int pipefd[2])
{
	int i;
	char *str;
	//t_cmd *initial_cmd;
	t_cmd *cmd;

	i = 0;
	//initial_cmd = NULL;
	cmd = NULL;
	str = buffer;
	while (str[i])
	{
		//cmd = ft_lstadd_back(&initial_cmd, ft_new_cmd(&str[i]));
		ft_cmdadd_back(&cmd, ft_new_cmd(&str[i]));
		if (cmd == NULL)
			return (0);
		if (str[i] == '\0')
			break;
		while (str[i] && ft_strchr(";|<>", str[i]) == NULL)
			i++;
		while (str[i] && ft_strchr(";|<>", str[i]) != NULL)
			i++;
	}
	if (cmd == NULL)
		return (0);
	return (ft_handle_command(cmd, shell_c, pipefd));
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
	/*int ret;
	  char buffer[ARG_MAX + 1];

	  (void)quit; // ===== DELETE =====
	  write(1, "$ ", 2);
	  ret = read(0, buffer, ARG_MAX);
	  if (ret < 0)
	  return (-1);
	  else if (ret == 0)
	  {
	  write(1, "exit\n", 5);
	  write(shell_c->fd[1], EXIT_SHELL, 3);
	  write(shell_c->fd[1], "\x1F\x1E", 2);
	  return (0);
	  }
	  buffer[ret - 1] = '\0';
	  return (ft_init_args_tree(buffer, shell_c, pipefd));*/
	struct termios	termios_c;
	t_icanon		icanon;
	
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
	write(shell_c->fd[1], ADD_HISTORY, 3);
	write(shell_c->fd[1], "\x1F", 1);
	write(shell_c->fd[1], icanon.line, ft_strlen(icanon.line));
	write(shell_c->fd[1], "\x1E", 1);
	ft_init_args_tree(icanon.line, shell_c, pipefd);
	return (0);
}
