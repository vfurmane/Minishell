/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 14:25:10 by earnaud           #+#    #+#             */
/*   Updated: 2021/05/09 11:50:47 by vfurmane         ###   ########.fr       */
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

int ft_echo(t_config *shell_c, char **args, int output_fd);
int ft_cd(t_config *shell_c, char **args, int output_fd);
int ft_pwd(t_config *shell_c, char **args, int output_fd);
int ft_export(t_config *shell_c, char **args, int output_fd);
int ft_unset(t_config *shell_c, char **args, int output_fd);
int ft_env(t_config *shell_c, char **args, int output_fd);
int ft_exit(t_config *shell_c, char **args, int output_fd);
int ft_cd2(char *str); /* ===== DELETE ===== */
char *ft_convert_env(char *source, char **env); /* ===== DELETE ===== */

#endif
