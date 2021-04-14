/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:09:18 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/14 16:21:17 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	int quit;
	int id;
	int status;
	int pipefd[2];
	char **environment;

	(void)argc;
	(void)argv;
	environment = ft_env_malloc(envp);
	export_list = ft_env_malloc(envp);
	quit = 0;
	while (!quit)
	{
		pipe(pipefd);
		pipe(pipexport);
		id = fork();
		if (id)
		{
			signal(SIGINT, nothing);
			wait(&status);
			close(pipefd[1]);
			close(pipexport[1]);
			if (WEXITSTATUS(status) == S_SIGQUITSH)
				quit = 1;
			else if (WEXITSTATUS(status) == S_SIGUPENV)
			{
				ft_update_env(pipefd, &environment);
				ft_update_env(pipexport, &export_list);
			}
			signal(SIGINT, SIG_DFL);
			close(pipefd[0]);
			close(pipexport[0]);
		}
		else
		{
			close(pipefd[0]);
			close(pipexport[0]);
			if (ft_prompt(&quit, environment, pipefd) == -1)
				return (1);
			close(pipefd[1]);
			close(pipexport[1]);
			exit(0);
		}
	}
	return (0);
}
