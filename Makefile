# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/06 14:15:36 by earnaud           #+#    #+#              #
#    Updated: 2021/03/29 19:40:30 by earnaud          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= MiniShell
CC			= gcc
CFLAGS		= -g #-Wall -Wextra -Werror
INCLUDES	= -Iincludes/
OBJ_DIR		= obj/
SRCS_DIR 	= srcs/
NEED		= libft

NEEDA		= $(NEED)/*.a

FILES		=  main.c


SRCS		= $(addprefix $(SRCS_DIR), $(FILES))
OBJ			= $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ) dependencies
		@echo MiniShell on the way...
		@$(CC) $(CFLAGS) $(OBJ) $(INCLUDES)\
		 $(NEEDA) \
		-o $(NAME)
		@echo success

dependencies :
		@echo building dependencies
		make -C $(NEED)
		@echo dependencies success

clean:
		make clean -C $(NEED)
		rm -f $(OBJ)
		@echo clean done
		
fclean: clean
		make fclean -C $(NEED)
		rm -f $(NAME)
		@echo fclean done

re: fclean all

.PHONY: clean fclean all re dependencies
