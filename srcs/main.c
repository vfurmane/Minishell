#include "../includes/Minishell.h"

int env_write(char *str, int fd)
{
	int i = 0;
	char str2[ARG_MAX];
	while (*(str + i) && *(str + i) != ' ' && *(str + i) != '\n')
	{
		str2[i] = *(str + i);
		i++;
	}
	str2[i] = '\0';
	write(fd, getenv(str2), ft_strlen(getenv(str2)));
	return (i + 1);
}

void echo(int n, char *str, int fd)
{
	int i = 0;
	while (str[i] && (!n || i <= ft_strlen(str)))
	{
		if (str[i] == '$')
			i += env_write(str + i + 1, fd);
		write(fd, str + i++, 1);
	}
}

int main()
{
	int i;
	char buf_line[ARG_MAX];
	int fd = STDOUT_FILENO;

	while (read(STDIN_FILENO, buf_line, ARG_MAX))
	{
		echo(1, buf_line, fd);
		i = 0;
		while (i < ARG_MAX)
		{
			buf_line[i] = 0;
			i++;
		}
	}
}