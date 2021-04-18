/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 13:42:36 by vfurmane          #+#    #+#             */
/*   Updated: 2021/04/18 15:47:23 by vfurmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>

typedef struct		s_next
{
	struct s_next	*next;
}					t_next;

size_t				ft_arrlen(void *str);
void				*ft_bzero(void *str, size_t len);
void				*ft_calloc(size_t len, size_t size);
int					ft_isalpha(int chr);
int					ft_isdigit(int chr);
void				*ft_lstadd_back(void *lst, void *new);
void				*ft_lstlast(void *lst);
int					ft_lstsize(void *lst);
void				*ft_memcpy(void *dest, const void *src, size_t len);
int					ft_strccmp(const char *str1, const char *str2, int chr);
char				*ft_strcdup(const char *str, int chr);
char				*ft_strchr(const char *str, int chr);
char				*ft_strcidup(const char *str, int chr);
char				**ft_strarrdup(char **arr);
int					ft_strcmp(const char *str1, const char *str2);
char				*ft_strdup(const char *str);
char				*ft_strinstr(const char *str, const char *sep);
size_t				ft_strlen(const char *str);
char				*ft_strndup(const char *str, int len);
char				*ft_strnstr(const char *big,
					const char *little, size_t len);


#endif
