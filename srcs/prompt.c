/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:09:52 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/25 15:01:31 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_display_prompt(char *prompt)
{
	return (write(1, prompt, ft_strlen(prompt)));
}

t_dlist	*ft_new_history_line(void)
{
	t_dlist	*elm;

	elm = malloc(sizeof(*elm));
	if (elm == NULL)
		return (NULL);
	elm->next = NULL;
	elm->previous = NULL;
	elm->content = ft_calloc(sizeof(elm), ARG_MAX + 1);
	return (elm);
}

static void	ft_sigint_prompt(int code)
{
	if (code == SIGINT)
		exit(S_SIGINT_PROMPT);
}

int	ft_prompt(t_config *shell_c)
{
	int				ret;
	struct termios	termios_c;
	t_icanon		icanon;
	t_dlist			*history_backup;

	signal(SIGINT, ft_sigint_prompt);
	tcgetattr(0, &termios_c);
	termios_c.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, 0, &termios_c);
	ft_bzero(&icanon, sizeof(icanon));
	ft_display_prompt(shell_c->prompt);
	ft_lstadd_front(&shell_c->history, ft_new_history_line());
	history_backup = shell_c->history;
	icanon.line = shell_c->history->content;
	if (shell_c->history->next != NULL)
		shell_c->history->next->previous = shell_c->history;
	ft_read_icanon(shell_c, &icanon);
	tcsetattr(0, 0, &shell_c->termios_backup);
	signal(SIGINT, SIG_DFL);
	if (icanon.line[0] == '\0')
		return (S_SIGIGN);
	ft_write_pipe(ADD_HISTORY, icanon.line, NULL, shell_c->fd[1]);
	shell_c->history = history_backup;
	ret = ft_init_args_tree(shell_c, icanon.line);
	return (ret);
}
