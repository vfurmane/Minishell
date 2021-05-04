/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   router.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 11:52:44 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/04 10:46:52 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_command_not_found(const char *command, int fd)
{
	write(fd, "minishell: ", 12);
	write(fd, command, ft_strlen(command));
	write(fd, ": command not found\n", 21);
}

void ft_kill_child(int id)
{
	kill(id, SIGINT);
}

int ft_route_file_from(const char *file_name, t_config *shell_c)
{
	char	*temp;
	char	*file_name_fix;
	char	*final_str;
	char	*buf_temp;
	int		fd;
	int		ret;

	ret = 1;
	if (file_name[0] != '/' || file_name[0] != '~')
	{
		temp = ft_strjoin(ft_getenv(shell_c->envp, "PWD"), "/"); //check if null
		file_name_fix = ft_strjoin(temp, file_name);			 //check if null
		free(temp);
	}
	else
		file_name_fix = ft_strdup(file_name);
	fd = open(file_name_fix, O_RDONLY); //check if error
	while (ret != -1 && ret)
	{
		if (final_str)
		{
			buf_temp = ft_strdup(final_str);
			free(final_str);
		}
		else
			buf_temp = NULL;
		temp = malloc(sizeof(char) * 421);
		ret = read(fd, temp, 420);
		final_str = ft_strjoin(buf_temp, temp);
		free(temp);
		free(buf_temp);
	}
	if (write(STDOUT_FILENO, final_str, ft_strlen(final_str)) == -1)
		return (-1);
	return (0);
}

int ft_route_file_to(const char *file_name, t_config *shell_c, int happen)
{
	char	*file_name_fix;
	char	*temp;
	int		fd;
	int		ret;
	char	*buf_temp;
	char	*final_str;

	ret = 1;
	final_str = NULL;
	if (file_name[0] != '/' || file_name[0] != '~')
	{
		temp = ft_strjoin(ft_getenv(shell_c->envp, "PWD"), "/"); //check if null
		file_name_fix = ft_strjoin(temp, file_name);			 //check if null
		free(temp);
	}
	else
		file_name_fix = ft_strdup(file_name);
	if (happen)
		fd = open(file_name_fix, O_RDWR | O_APPEND | O_CREAT, 0666); //check if error
	else
		fd = open(file_name_fix, O_RDWR | O_CREAT, 0666); //check if error
	while (ret != -1 && ret)
	{
		if (final_str)
		{
			buf_temp = ft_strdup(final_str);
			free(final_str);
		}
		else
			buf_temp = NULL;
		temp = malloc(sizeof(char) * 421);
		ret = read(STDIN_FILENO, temp, 420);
		final_str = ft_strjoin(buf_temp, temp);
		free(temp);
		free(buf_temp);
	}
	if (write(fd, final_str, ft_strlen(final_str)) == -1)
		return (-1);
	return (0);
}

int ft_route_command(const char *command, char **args, int fd[2], char **line, t_config *shell_c, t_cmd *cmd)
{
	int ret;
	int id;
	int	status;

	(void)fd;
	(void)cmd;
	ret = 0;

	// id = fork();
	// if (id)
	// {
	// 	if (cmd->separator == 42)
	// 	{
	// 		close(cmd->fd[0]);
	// 		dup2(cmd->fd[1], STDOUT_FILENO);
	// 		close(cmd->fd[1]);
	// 	}
	// 	//program here
	// 	wait(&ret);
	// 	return (ret);
	// }
	// if (cmd->separator == 42)
	// {
	// 	close(cmd->fd[1]);
	// 	dup2(STDIN_FILENO, cmd->fd[0]);
	// 	close(cmd->fd[0]);
	// }
	// //next program here

	status = 0;
	if (ft_strcmp("echo", command) == 0)
		ret = ft_echo(args, STDOUT_FILENO);
	else if (ft_strcmp("cd", command) == 0)
		ret = ft_cd(args, STDOUT_FILENO, shell_c);
	else if (ft_strcmp("pwd", command) == 0)
		ret = ft_pwd(args, STDOUT_FILENO);
	else if (ft_strcmp("export", command) == 0)
		ret = ft_export(args, STDOUT_FILENO, shell_c);
	else if (ft_strcmp("unset", command) == 0)
		ret = ft_unset(args, shell_c);
	else if (ft_strcmp("env", command) == 0)
		ret = ft_env(args, STDOUT_FILENO, shell_c->envp);
	else if (ft_strcmp("exit", command) == 0)
		ret = ft_exit(args, STDOUT_FILENO, shell_c);
	else if (ft_strchr(command, '/'))
	{
		id = fork();
		if (id)
			wait(&status);
		else
			ft_execve(line[0], line, NULL); //cas ou existe pas
	}
	else
	{
		id = fork();
		if (id)
			wait(&status);
		else
			if (!ft_exec(line, shell_c->envp))
			{
				ft_command_not_found(command, STDOUT_FILENO);
				exit(127);
			}
	}
	if (WIFEXITED(status))
		ret = WEXITSTATUS(status);
	return (ret);
	//maybe exit (0) here
}
