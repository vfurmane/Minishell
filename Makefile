# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/06 14:15:36 by earnaud           #+#    #+#              #
#    Updated: 2021/03/31 11:55:51 by vfurmane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_DIR 	= srcs/
FILES		=  main.c prompt.c
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

$(NAME):	$(OBJ)
			@$(CC) $(CFLAGS) $(OBJ) $(INCLUDES) -o $(NAME) $(LIBS)

clean:
			$(RM) $(OBJ)
		
fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
