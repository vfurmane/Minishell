/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:09:18 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/09 13:41:57 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	int quit;
	int id;
	int status;
	int pipefd[2];

	(void)argc;
	(void)argv;
	environement = ft_env_malloc(envp);
	quit = 0;
	while (!quit)
	{
		pipe(pipefd);
		pip[0] = pipefd[0];
		pip[1] = pipefd[1];
		id = fork();
		if (id)
		{
			signal(SIGINT, nothing);
			wait(&status);
			close(pip[1]);
			if (WEXITSTATUS(status) == S_SIGQUITSH)
				quit = 1;
			else if (WEXITSTATUS(status) == S_SIGUPENV)
				ft_update_env();
			signal(SIGINT, SIG_DFL);
			close(pip[0]);
		}
		else
		{
			close(pip[0]);
			if (ft_prompt(&quit) == -1)
				return (1);
			close(pip[1]);
			exit(0);
		}
	}
	return (0);
}
