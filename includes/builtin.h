/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 14:25:10 by earnaud           #+#    #+#             */
/*   Updated: 2021/04/19 18:16:03 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

typedef struct s_config t_config;

int ft_echo(char **args, int fd);
int ft_cd(char **args, int fd, char **envp, t_config *shell_c);
int ft_pwd(char **args, int fd);
int ft_export(char **args, int fd, t_config *shell_c, int quit);
int ft_unset(char **args, t_config *shell_c);
int ft_env(char **args, int fd, char **environment);
int ft_exit(char **args, int fd, t_config *shell_c);
char *ft_convert_env(char *source, char **env);

#endif
