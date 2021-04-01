/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 13:42:36 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/01 12:22:23 by earnaud          ###   ########.fr       */
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
char				*ft_strinstr(const char *str, const char *sep);
size_t				ft_strlen(const char *str);
char				*ft_strndup(const char *str, int len);
char				*ft_strnstr(const char *big,
					const char *little, size_t len);


#endif
