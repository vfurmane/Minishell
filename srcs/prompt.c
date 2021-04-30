/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:09:52 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/30 15:09:04 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_separator ft_set_separator(const char *str)
{
	if (str[0] == ';')
		return (EOCMD);
	else if (str[0] == '<') // not useful
		return (REDIR_LEFT); // not useful
	else if (str[0] == '>') // not useful
		if (str[1] == '>') // not useful
			return (REDIR_APPEND); // not useful
		else 						// not useful
			return (REDIR_RIGHT); // not useful
	else if (str[0] == '|')
		return (PIPE);
	else
		return (EOCMD);
}

int where_to_cut(char *const buffer)
{
	int i;

	i = 0;
	if (!buffer)
		return (0);
	while (buffer[i])
	{
		if (ft_strchr(";| ", buffer[i]))
			return (i);
		i++;
	}
	return (i);
}

char	*buffer_fix(char *const buffer)
{
	char *str;
	int count[2];

	count[0] = 0;
	count[1] = 0;
	str = malloc(sizeof(char) * ft_strlen(buffer)); //check if fail
	if (!str)
		return (NULL);
	while (buffer[count[0]] && !ft_strchr(";|", buffer[count[0]]))
	{
		if (ft_strchr("<>", buffer[count[0]]))
		{
			while (ft_strchr(" <>", buffer[count[0]]))
				count[0]++;
			while (buffer[count[0]] && !ft_strchr(" <>|;", buffer[count[0]]))
				count[0]++;
		}
		//else
			str[count[1]++] = buffer[count[0]++];
	}
	str[count[1]] = 0;
	return (str);
}

char	*ft_fix_openfiles(char *const buffer, t_cmd *cmd)
{
	char *file_name;
	char *file_name_fix;
	int i;
	int happen;
	char *temp;

	if (!buffer)
		return (0);
	i = 0;
	cmd->file = 0;
	happen = 0;
	while (buffer[i] && !ft_strchr("|;", buffer[i]))
	{
		if (ft_strchr("<>", buffer[i]))
		{
			if (buffer[i] == '<')
				cmd->from_to = BRACKET_FROM;
			else if (buffer[i] == '>')
				cmd->from_to = BRACKET_TO;
			if (buffer[i + 1] == '>')
			{
				happen = 1;
				i++;
			}
			i++;
			if (cmd->file)
				close(cmd->file);
			while (buffer[i] == ' ')
				i++;
			file_name = ft_strndup(buffer + i, where_to_cut(buffer + i));
			if (file_name[0] != '/' || file_name[0] != '~')
			{
				temp = ft_strjoin(ft_getenv(envptemp, "PWD"), "/"); //check if null
				file_name_fix = ft_strjoin(temp, file_name);		//check if null
				free(temp);
				free(file_name);
			}
			else
				file_name_fix = file_name;
			if (happen)
				cmd->file = open(file_name_fix, O_RDWR | O_APPEND | O_CREAT, 0666); //check if error
			else
				cmd->file = open(file_name_fix, O_RDWR | O_CREAT, 0666); //check if error
			free(file_name_fix);
		}
		else
			i++;
	}
	if (cmd->file)
		return (buffer_fix(buffer));
	return (NULL);
}

t_cmd *ft_new_cmd(char *const buffer)
{
	t_cmd	*cmd;
	char	*separator;
	char	*buffer_fix;

	cmd = malloc(sizeof(*cmd));
	if (cmd == NULL)
		return (NULL);


	buffer_fix = ft_fix_openfiles(buffer, cmd);
	//free(buffer);

	cmd->next = NULL;
	separator = ft_strinstr(buffer, ";|");
	if (separator == NULL)
		separator = &buffer[ft_strlen(buffer)];
	if (buffer_fix)
		cmd->str = buffer_fix;
	else
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
}

// int ft_nbr_cmd(char *str)
// {
// 	int i;
// 	int prec_char;

// 	i = 0;
// 	prec_char = 0;
// 	if (!str)
// 		return (i);
// 	while (*str)
// 	{
// 		if (*str == ';')
// 		{
// 			i++;
// 			while (*str == ';')
// 				str++;
// 		}
// 		else
// 			str++;
// 	}
// 	i++;
// 	return (i);
// }

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

// int ft_all_commands(char *const buffer, t_config *shell_c)
// {
// 	int i;
// 	int j;
// 	char **str;
// 	char *parsed;
// 	char *temp;

// 	temp = buffer;
// 	i = 0;
// 	j = 0;
// 	str = malloc(sizeof(char *) * ft_nbr_cmd(temp));
// 	while (i < ft_nbr_cmd((char*)buffer))
// 	{
// 		str[i] = ft_strcdup(temp, ';');
// 		temp += ft_in_str_where(temp, ';', 1);
// 		i++;
// 	}
// 	return(0); //the function to parse file and after launch init arg tree
// }

int ft_init_args_tree(char *const buffer, t_config *shell_c)
{
	int i;
	char *str;
	t_cmd *cmd;
	int bracket;
	//int to_from[2];

	i = 0;
	bracket = 0;
	//to_from[0] = 0;
	//to_from[1] = 0;
	cmd = NULL;
	str = buffer;

	envptemp = shell_c->envp; //temp the time that we can use get_env again

	while (str[i])
	{
		ft_cmdadd_back(&cmd, ft_new_cmd(&str[i]));
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
	return (ft_recursiv_command(cmd, shell_c, STDIN_FILENO, dup(STDOUT_FILENO)));
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
	//ft_all_commands(icanon.line, shell_c);
	ft_init_args_tree(icanon.line, shell_c);
	return (0);
}
