/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:09:18 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/06 14:09:50 by earnaud          ###   ########.fr       */
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

environement = envp;
	quit = 0;
	while (!quit)
	{
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
			exit(0);
		}
	}
	return (0);
}
