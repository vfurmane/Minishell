/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:09:18 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/12 13:57:07 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	int		quit;
	int		id;
	int		status;
	int		pipefd[2];
	char	**environement;

	(void)argc;
	(void)argv;
	environement = ft_env_malloc(envp);
	quit = 0;
	while (!quit)
	{
		pipe(pipefd);
		id = fork();
		if (id)
		{
			signal(SIGINT, nothing);
			wait(&status);
			close(pipefd[1]);
			if (WEXITSTATUS(status) == S_SIGQUITSH)
				quit = 1;
			else if (WEXITSTATUS(status) == S_SIGUPENV)
				ft_update_env(pipefd, &environement);
			signal(SIGINT, SIG_DFL);
			close(pipefd[0]);
		}
		else
		{
			close(pipefd[0]);
			if (ft_prompt(&quit, environement, pipefd) == -1)
				return (1);
			close(pipefd[1]);
			exit(0);
		}
	}
	return (0);
}
