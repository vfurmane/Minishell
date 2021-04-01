/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfurmane <vfurmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 13:42:36 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/01 12:33:52 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>

typedef struct		s_next
{
	struct s_next	*next;
}					t_next;

void				*ft_lstadd_back(void *lst, void *new);
void				*ft_lstlast(void *lst);
void				*ft_memcpy(void *dest, const void *src, size_t len);
char				*ft_strchr(const char *str, int chr);
int					ft_strcmp(const char *str1, const char *str2);
char				*ft_strinstr(const char *str, const char *sep);
size_t				ft_strlen(const char *str);
char				*ft_strndup(const char *str, int len);

#endif
