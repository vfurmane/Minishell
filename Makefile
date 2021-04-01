# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/06 14:15:36 by earnaud           #+#    #+#              #
#    Updated: 2021/04/01 13:39:38 by earnaud          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_DIR 	= srcs
FILES		=  main.c \
			   cmd.c \
			   prompt.c \
				builtin/ft_echo.c \
				ft_convert_env.c \
				utils/ft_lstadd_back.c \
				utils/ft_lstlast.c \
				utils/ft_memcpy.c \
				utils/ft_strchr.c \
				utils/ft_strinstr.c \
				utils/ft_strjoin.c \
				utils/ft_strlcpy.c \
				utils/ft_strlen.c \
				utils/ft_strndup.c \
				utils/div.c \
				utils/ft_strnstr.c \
				builtin/ft_cd.c
				
SRCS		= $(addprefix $(SRCS_DIR)/, $(FILES))
OBJS		= $(SRCS:.c=.o)
NAME		= Minishell
CC			= clang
CFLAGS		= -g -Wall -Wextra -Werror
LIBS		= -lncurses
INCLUDES	= -Iincludes

%.o:		%.c
			$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

$(NAME) : $(OBJS)
		@$(CC) $(CFLAGS) $(OBJS) $(INCLUDES)\
		-o $(NAME) $(LIBS)

clean:
			$(RM) $(OBJS)
		
fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
