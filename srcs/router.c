/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   router.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 11:52:44 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/28 09:13:15 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_a_builtin(t_config *shell_c, char **argv, int *ret)
{
	int				builtin_id;
	const char		*builtins[8] = {"echo", "cd", "pwd", "export", "unset",
										"env", "exit", NULL};
	const t_builtin	funcs[7] = {ft_echo, ft_cd, ft_pwd, ft_export, ft_unset,
									ft_env, ft_exit};

	ft_strarrstr(builtins, argv[0], &builtin_id);
	if (builtin_id == -1)
		return (0);
	*ret = (funcs[builtin_id])(shell_c, &argv[1], STDOUT_FILENO);
	return (1);
}

static int	return_free(t_config *shell_c, char **argv, int ret)
{
	if (ret == 127)
		ft_stderr_message(argv[0], ": No such file or directory", NULL,
			127);
	if (ret == 126)
		ft_stderr_message(argv[0], ": Is a directory", NULL,
			126);
	free_neo(argv);
	free_shell(shell_c);
	return (ret);
}

static int	ft_search_and_execute_file(t_config *shell_c, char **argv)
{
	struct stat	file_stat;

	if (stat(argv[0], &file_stat) == -1)
		exit(return_free(shell_c, argv, 127));
	if (file_stat.st_mode & 040000)
		exit(return_free(shell_c, argv, 126));
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	ft_execve(argv[0], argv, shell_c->envp);
	return_free(shell_c, argv, 0);
	return (127);
}

static int	ft_search_and_execute_command(t_config *shell_c, char **argv)
{
	if (ft_getenv(shell_c->envp_list, "PATH") == NULL)
		exit(ft_stderr_message(argv[0], ": No such file or directory", NULL,
				127));
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (argv[0][0] == '\0' || ft_strcmp(".", argv[0]) == 0
		|| !ft_exec(shell_c, argv))
		ft_stderr_message(argv[0], ": command not found", NULL, 0);
	free_neo(argv);
	free_shell(shell_c);
	return (127);
}

int	ft_route_command(t_config *shell_c, char **argv)
{
	int			ret;
	int			id;
	int			status;

	ret = 0;
	status = 0;
	id = fork();
	if (id == -1)
		ret = ft_stderr_message("fork: ", strerror(errno), NULL, 127);
	else if (id != CHILD_PROCESS)
		wait(&status);
	else
	{
		if (ft_is_a_builtin(shell_c, argv, &ret))
			exit(ret);
		else if (ft_strchr(argv[0], '/'))
			exit(ft_search_and_execute_file(shell_c, argv));
		else
			exit(ft_search_and_execute_command(shell_c, argv));
	}
	if (WIFSIGNALED(status))
		ret += 128 + WTERMSIG(status);
	else if (WIFEXITED(status))
		ret = WEXITSTATUS(status);
	return (ret);
}
