/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 08:52:02 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/28 08:56:41 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	int	i;

	printf("argc -> %d\n\n", argc);
	printf("argv:\n");
	i = -1;
	while (argv[++i])
		printf("  %02d. %s\n", i, argv[i]);
	printf("\nenvp:\n");
	i = -1;
	while (envp[++i])
		printf("  %02d. %s\n", i, envp[i]);
	return (0);
}
