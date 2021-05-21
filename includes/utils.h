/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 13:42:36 by vfurmane          #+#    #+#             */
/*   Updated: 2021/05/21 13:21:53 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <unistd.h>

typedef struct		s_next
{
	struct s_next	*next;
}					t_next;

size_t				ft_arrlen(void *str);
void				*ft_bzero(void *str, size_t len);
void				*ft_calloc(size_t len, size_t size);
int					ft_isalpha(int chr);
int					ft_isdigit(int chr);
void				*ft_lstadd_front(void *lst, void *new);
void				*ft_lstadd_back(void *lst, void *new);
void				*ft_lstlast(void *lst);
int					ft_lstsize(void *lst);
void				*ft_memcpy(void *dest, const void *src, size_t len);
void				*ft_memmove(void *dest, const void *src, size_t len);
void				*ft_memset(void *str, int c, size_t n);
int					ft_putchar(int chr);
char				**ft_split(char const *s, char c);
char				*ft_static_itoa(int nbr);
char				**ft_strarrdup(char **arr);
char				*ft_strarrstr(const char **arr, const char *str,
					int *index);
int					ft_strccmp(const char *str1, const char *str2, int chr);
char				*ft_strcdup(const char *str, int chr);
char				*ft_strchr(const char *str, int chr);
char				*ft_strcidup(const char *str, int chr);
int					ft_strcmp(const char *str1, const char *str2);
size_t				ft_strcpy(char *dest, const char *src);
char				*ft_strdup(const char *str);
char				*ft_strinstr(const char *str, const char *sep);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
size_t				ft_strlen(const char *str);
char				*ft_strndup(const char *str, int len);
char				*ft_strnstr(const char *big,
					const char *little, size_t len);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strinstr_last(const char *str, const char *sep);
int					ft_in_str_where(char *str, char c, int last);

#endif
