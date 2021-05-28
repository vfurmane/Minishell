/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:09:18 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/28 10:07:26 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_increment_shlvl(t_config *shell_c)
{
	int		shlvl_nbr;
	char	*shlvl;

	shlvl_nbr = ft_atoi(ft_getenv(shell_c->envp_list, "SHLVL"));
	shlvl = ft_strjoin("SHLVL=", ft_static_itoa(shlvl_nbr + 1));
	ft_add_env(shell_c, shlvl);
	free(shlvl);
	return (0);
}

static int	ft_init_shell(t_config *shell_c, char **envp)
{
	if (__APPLE__)
	{
		printf("\033[33mYou are using minishell on an Apple platform, "
			"some features may be unreliable.\033[0m\n");
	}
	if (tgetent(NULL, getenv("TERM")) == -1)
	{
		printf("\033[31mA very unfortunate error made the shell unusuable. "
			"Aborting...\033[0m\n");
		return (-1);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (ft_parse_envp(envp, shell_c) == -1)
		return (ft_stderr_message("the environment variables could not"
				"be parsed", NULL, NULL, -1));
	ft_increment_shlvl(shell_c);
	shell_c->quit = 0;
	shell_c->prompt = "$ ";
	shell_c->history = NULL;
	shell_c->exit_code = 0;
	return (0);
}

static int	ft_process_child_exit(t_config *shell_c)
{
	int	status;

	wait(&status);
	tcsetattr(0, 0, &shell_c->termios_backup);
	if (WEXITSTATUS(status) != S_SIGIGN)
		shell_c->exit_code = WEXITSTATUS(status);
	if (shell_c->exit_code >= 134)
		ft_stderr_message("got signal ",
			ft_static_itoa(shell_c->exit_code - 128), NULL, 0);
	ft_update_shell(shell_c);
	if (WTERMSIG(status) == SIGINT || WEXITSTATUS(status) == 128 + SIGINT)
		write(1, "\n", 1);
	else if (WTERMSIG(status) == SIGQUIT
		|| WEXITSTATUS(status) == 128 + SIGQUIT)
		write(2, "Quit (core dumped)\n", 19);
	return (0);
}

static int	ft_process_child_prompt(t_config *shell_c)
{
	int	ret;

	signal(SIGINT, SIG_DFL);
	ret = ft_prompt(shell_c);
	if (ret == -1)
		exit(127);
	free_shell(shell_c);
	exit(ret);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int			id;
	int			ret;
	t_config	shell_c;

	(void)argc;
	(void)argv;
	if (ft_init_shell(&shell_c, envp) == -1)
		return (1);
	while (!shell_c.quit)
	{
		tcgetattr(0, &shell_c.termios_backup);
		pipe(shell_c.fd);
		id = fork();
		if (id == -1)
			return (ft_stderr_message("could not fork: ", strerror(errno),
					NULL, 1));
		else if (id != CHILD_PROCESS)
			ft_process_child_exit(&shell_c);
		else
			ft_process_child_prompt(&shell_c);
	}
	ret = (int)shell_c.exit_code;
	free_shell(&shell_c);
	return (ret);
}
