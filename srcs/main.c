/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:09:18 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/07 16:06:01 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	int quit;	
	int id;
	int	status;

(void)argc;
(void)argv;
environement = ft_env_malloc(envp);
	quit = 0;
	while (!quit)
	{
		pipe(pip);
		id = fork();
		if (id)
		{
			signal(SIGINT, nothing);
			wait(&status);
			if (WIFEXITED(status) && WEXITSTATUS(status) == S_SIGQUITSH)
				quit = 1;
			signal(SIGINT, SIG_DFL);
		}
		else
		{
			if (ft_prompt(&quit) == -1)
				return (1);
			ft_update_env();
			exit(0);
		}
	}
	return (0);
}