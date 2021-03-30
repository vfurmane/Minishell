#ifndef MINISHELL_H
# define MINISHELL_H
#include <linux/limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

typedef struct s_all
{
	char str[ARG_MAX];
	int str_i;
} t_all;

#endif