/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 14:25:10 by earnaud           #+#    #+#             */
/*   Updated: 2021/05/04 10:45:14 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

typedef struct s_config t_config;

typedef struct	s_echo
{
	int			e_flag;
	int			e_cap_flag;
	int			n_flag;
}				t_echo;

int ft_echo(char **args, int fd);
int ft_cd(char **args, int fd, t_config *shell_c);
int ft_cd2(char *str);
int ft_pwd(char **args, int fd);
int ft_export(char **args, int fd, t_config *shell_c);
int ft_unset(char **args, t_config *shell_c);
int ft_env(char **args, int fd, char **environment);
int ft_exit(char **args, int fd, t_config *shell_c);
char *ft_convert_env(char *source, char **env);

#endif
