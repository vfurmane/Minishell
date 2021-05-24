/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:09:18 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/24 17:38:15 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			main(int argc, char **argv, char **envp)
{
	int			ret;
	int			id;
	int			status;
	t_config	shell_c;

	(void)argc; /* ===== DELETE ===== */
	(void)argv; /* ===== DELETE ===== */
	if (__APPLE__)
	{
		printf("\033[33mYou are using minishell on an Apple platform, "
				"some features may be unreliable.\033[0m\n");
	}
	if (tgetent(NULL, getenv("TERM")) == -1)
	{
		printf("\033[31mA very unfortunate error made the shell unusuable. "
				"Aborting...\033[0m\n");
		return (1);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (ft_parse_envp(envp, &shell_c) == -1)
		return (ft_stderr_message("the environment variables could not"
									"be parsed", NULL, NULL, 1));
	shell_c.quit = 0;
	shell_c.prompt = "$ ";
	shell_c.history = NULL;
	shell_c.exit_code = 0;
	while (!shell_c.quit)
	{
		tcgetattr(0, &shell_c.termios_backup);
		pipe(shell_c.fd);
		id = fork();
		if (id == -1)
			return (ft_stderr_message("could not fork: ", strerror(errno),
				NULL, 1));
		else if (id != CHILD_PROCESS)
		{
			wait(&status);
			tcsetattr(0, 0, &shell_c.termios_backup);
			if (WEXITSTATUS(status) != S_SIGINT_PROMPT && WEXITSTATUS(status) 		!= S_SIGIGN)
				shell_c.exit_code = WEXITSTATUS(status);
			if (shell_c.exit_code >= 134)
				ft_stderr_message("got signal ", ft_static_itoa(shell_c.exit_code - 128), NULL, 0);
			ft_update_shell(&shell_c);
			if (WTERMSIG(status) == SIGINT || WEXITSTATUS(status) == 				S_SIGINT_PROMPT)
				write(STDOUT_FILENO, "\n", 1);
			else if (WTERMSIG(status) == SIGQUIT)
				write(2, "Quit (core dumped)\n", 19);
		}
		else
		{
			signal(SIGINT, SIG_DFL);
			ret = ft_prompt(&shell_c);
			if (ret == -1)
				return (1);
			free_shell(&shell_c);
			exit(ret);
		}
	}
	ret = (int)shell_c.exit_code;
	free_shell(&shell_c);
	return (ret);
}
