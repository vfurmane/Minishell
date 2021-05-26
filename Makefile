# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/06 14:15:36 by earnaud           #+#    #+#              #
#    Updated: 2021/05/26 13:48:39 by vfurmane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_DIR 	= srcs

FILES		= args_tree.c \
			  cmd.c \
			  env.c \
			  exec.c \
			  main.c \
			  prompt.c \
			  put.c \
			  router.c \
			  pars_files.c \
			  pars_command.c \
			  parsing_len.c \
			  parsing_states.c \
			  skip.c \
			  split_args.c \
			  update_env.c \
			  update_history.c \
			  update_shell.c \
			  free.c \
			  $(addprefix builtin/, \
			  cd.c \
			  echo.c \
			  env.c \
			  exit.c \
			  export.c \
			  pwd.c \
			  unset.c) \
			  $(addprefix termcaps/, \
			  ctrl.c \
			  escape_code.c \
			  put.c \
			  read.c) \
			  $(addprefix utils/, \
			  ft_arrlen.c \
			  ft_bzero.c \
			  ft_calloc.c \
			  ft_isalpha.c \
			  ft_isdigit.c \
			  ft_lstadd_back.c \
			  ft_lstadd_front.c \
			  ft_lstlast.c \
			  ft_lstsize.c \
			  ft_memcpy.c \
			  ft_memmove.c \
			  ft_memset.c \
			  ft_putchar.c \
			  ft_split.c \
			  ft_static_itoa.c \
			  ft_strarrdup.c \
			  ft_strarrstr.c \
			  ft_strccmp.c \
			  ft_strcdup.c \
			  ft_strchr.c \
			  ft_strcidup.c \
			  ft_strcmp.c \
			  ft_strcpy.c \
			  ft_strdup.c \
			  ft_strinstr.c \
			  ft_strjoin.c \
			  ft_strlcpy.c \
			  ft_strlen.c \
			  ft_strndup.c \
			  ft_strnstr.c \
			  ft_substr.c)

SRCS		= $(addprefix $(SRCS_DIR)/, $(FILES))
OBJS		= $(SRCS:.c=.o)
NAME		= minishell
CC			= clang
CFLAGS		= -g -Wall -Wextra -Werror
LIBS		= -lncurses
INCLUDES	= -Iincludes

%.o:		%.c
			$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) -o $(NAME) $(LIBS)

clean:
			$(RM) $(OBJS)
		
fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
