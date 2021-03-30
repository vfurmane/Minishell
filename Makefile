# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/06 14:15:36 by earnaud           #+#    #+#              #
#    Updated: 2021/03/30 17:50:55 by earnaud          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= Minishell
CC			= gcc
CFLAGS		= -g -Wall -Wextra -Werror
INCLUDES	= -Iincludes/
SRCS_DIR 	= srcs/

FILES		=  main.c \
				ft_convert_env.c \
				ft_echo.c \
				utils/ft_strjoin.c \
				utils/ft_strlcpy.c \
				utils/ft_strlen.c


SRCS		= $(addprefix $(SRCS_DIR), $(FILES))
OBJ			= $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ)
		@$(CC) $(CFLAGS) $(OBJ) $(INCLUDES)\
		-o $(NAME)

clean:
		rm -f $(OBJ)
		
fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re
