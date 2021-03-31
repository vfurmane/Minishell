# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/06 14:15:36 by earnaud           #+#    #+#              #
#    Updated: 2021/03/31 13:41:09 by earnaud          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_DIR 	= srcs/
FILES		=  main.c \
				ft_echo.c \
				ft_convert_env.c \
				utils/ft_strjoin.c \
				utils/ft_strlcpy.c \
				utils/ft_strlen.c \
				
SRCS		= $(addprefix $(SRCS_DIR), $(FILES))
OBJS		= $(SRCS:.c=.o)
NAME		= Minishell
CC			= clang
CFLAGS		= -g -Wall -Wextra -Werror
LIBS		= -lncurses
INCLUDES	= -Iincludes/
RM			= rm -f

%.o:		%.c
			$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $^ $(INCLUDES) -o $@ $(LIBS)

clean:
			$(RM) $(OBJS)
		
fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
