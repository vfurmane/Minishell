/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 17:48:54 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/31 12:19:57 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <linux/limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "builtin.h"

size_t ft_strlen(const char *str);
char *ft_strjoin(char const *s1, char const *s2);
size_t ft_strlcpy(char *dest, const char *src, size_t size);


#endif