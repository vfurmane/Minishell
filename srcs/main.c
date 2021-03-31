#include "minishell.h"

void simple_echotest(int fd)
{
	char str[ARG_MAX];
	char *temp;
	int i;
	while (read(fd, str, ARG_MAX))
	{
		i = 0;
		temp = ft_convert_env(str);
		ft_echo(0, temp, STDOUT_FILENO);
		while (i < ARG_MAX)
			str[i++] = 0;
		free(temp);
	}
}

int main()
{
	ft_sub_echo(0, "\nthis is a test\n", STDOUT_FILENO);
	signal(SIGINT, nothing);
	wait(0);
	printf("\nwhere in main, now enter in a infinite loop\n");
	fflush(stdout);
	int i = 1;
	while (i)
		i = 1;
}