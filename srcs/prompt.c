/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:09:52 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/19 16:00:28 by vfurmane         ###   ########.fr       */
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

int	ft_putchar(int chr)
{
	write(1, &chr, 1);
	return ((int)chr);
}

int	ft_insert_char(char *str, int column, int chr)
{
	int	i;

	i = ft_strlen(&str[column]) + 1;
	while (--i >= 0)
		str[column + i + 1] = str[column + i];
	str[column] = chr;
	return (ft_strlen(str));
}

int	ft_delete_char(char *str, int column)
{
	int	i;
	int	len;

	len = ft_strlen(&str[column]) + 1;
	column--;
	i = -1;
	while (++i < len)
		str[column + i] = str[column + i + 1];
	return (ft_strlen(str));
}

int	ft_ctrl_d(int write_pipe, char *line, int column, int i)
{
	if (i == 0)
	{
		write(1, "exit\n", 5);
		write(write_pipe, EXIT_SHELL, 3);
		write(write_pipe, "\x1F\x1E", 2);
		return (0);
	}
	else if (column < i)
	{
		i = ft_delete_char(line, column + 1);
		tputs(clr_eol, 1, ft_putchar);
	}
	return (0);
}

int	ft_backspace(char *line, int *column, int *i)
{
	*i = ft_delete_char(line, (*column)--);
	tputs(tgoto(cursor_left, 0, 0), 1, ft_putchar);
	tputs(clr_eol, 1, ft_putchar);
	return (0);
}

int	ft_ctrl_l(char *line)
{
	tputs(save_cursor, 1, ft_putchar);
	tputs(clear_screen, 1, ft_putchar);
	write(1, "$ ", 2);
	write(1, line, ft_strlen(line));
	tputs(restore_cursor, 1, ft_putchar);
	tputs(tgoto(row_address, 0, 0), 1, ft_putchar);
	return (0);
}

int	ft_escape_code(char code, int *column, int i)
{
	if (code == 'D' && *column > 0)
	{
		tputs(tgoto(cursor_left, 0, 0), 1, ft_putchar);
		(*column)--;
	}
	else if (code == 'C' && *column < i)
	{
		tputs(tgoto(cursor_right, 0, 0), 1, ft_putchar);
		(*column)++;
	}
	return (0);
}

int	ft_rewrite_line(char *line, int column, int eol)
{
	tputs(save_cursor, 1, ft_putchar);
	while (column < eol)
		ft_putchar(line[column++]);
	tputs(restore_cursor, 1, ft_putchar);
	return (0);
}

int	ft_read_icanon(t_config *shell_c, char *line)
{
	int				i;
	int				ret;
	int				column;
	unsigned char	buffer[3];

	i = 0;
	ret = 1;
	column = 0;
	while (ret > 0 && i < ARG_MAX)
	{
		ret = read(0, buffer, 3);
		if (buffer[0] == 4)
			ret = ft_ctrl_d(shell_c->fd[1], line, column, i);
		else if (buffer[0] >= 32 && buffer[0] <= 126)
		{
			i = ft_insert_char(line, column++, buffer[0]);
			ft_putchar(buffer[0]);
		}
		else if (buffer[0] == 127 && column > 0)
			ft_backspace(line, &column, &i);
		else if (buffer[0] == '\f')
			ft_ctrl_l(line);
		else if (buffer[0] == '\n')
		{
			ft_putchar('\n');
			ret = 0;
		}
		else if (buffer[0] == 27 && buffer[1] == 91)
			ft_escape_code(buffer[2], &column, i);
		else
			tputs(bell, 1, ft_putchar);
		ft_rewrite_line(line, column, i);
	}
	line[i] = '\0';
	return (0);
}

int ft_prompt(int *quit, t_config *shell_c, int pipefd[2])
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
	char			*line;
	
	(void)quit; // ===== DELETE =====
	tgetent(NULL, getenv("TERM"));
	tcgetattr(0, &termios_c);
	termios_c.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, 0, &termios_c);
	line = ft_calloc(sizeof(*line), ARG_MAX + 1);
	write(1, "$ ", 2);
	ft_read_icanon(shell_c, line);
	termios_c.c_lflag &= (ICANON | ECHO);
	tcsetattr(0, 0, &termios_c);
	ft_init_args_tree(line, shell_c, pipefd);
	free(line);
	return (0);
}
