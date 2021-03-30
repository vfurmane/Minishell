/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 12:13:29 by vfurmane          #+#    #+#             */
/*   Updated: 2021/03/30 12:47:43 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr_fd(const char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(fd, str, i);
}

int		main(void)
{
	int	pipefd[2];
	
	if (pipe(pipefd) == -1)
		return (1);
	ft_putstr_fd("Hello World\n", 1);
	//ft_putstr_fd("Hello World\n", pipefd[1]);
	return (0);
}
