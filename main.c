#include <term.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define ARG_MAX 131072

int	ft_putchar(int chr)
{
	write(1, &chr, 1);
	return ((int)chr);
}

int	main(void)
{
	struct termios	termios_c;
	int				ret;
	int				i;
	char			*line;
	unsigned char	buffer[3];
	char			*cm, *DO, *UP, *LE, *RI;
	char			*arrow[4] = {	"UP",
		"DOWN",
		"RIGHT",
		"LEFT"};

	tgetent(NULL, getenv("TERM"));
	cm = tgetstr("cm", NULL);
	DO = tgetstr("DO", NULL);
	UP = tgetstr("UP", NULL);
	LE = tgetstr("LE", NULL);
	RI = tgetstr("RI", NULL);
	tcgetattr(0, &termios_c);
	termios_c.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, 0, &termios_c);
	while (1)
	{
		i = 0;
		ret = 1;
		line = malloc(sizeof(*line) * (ARG_MAX + 1));
		while (ret > 0 && i < ARG_MAX)
		{
			ret = read(0, buffer, 3);
			if (buffer[0] == 4)
				return (0); /* break the while here */
			if (buffer[0] >= 32 && buffer[0] <= 126)
			{
				ft_putchar(buffer[0]);
				line[i++] = buffer[0];
				//tputs(tgoto(RI, 0, 1), 1, ft_putchar);
			}
			else if (buffer[0] == 127)
			{
				tputs(tgoto(LE, 0, 0), 1, ft_putchar);
				ft_putchar(' ');
				tputs(tgoto(LE, 0, 0), 1, ft_putchar);
				buffer[--i] = '\0';
			}
			else if (buffer[0] == '\n')
			{
				ft_putchar('\n');
				ret = 0;
			}
			else if (buffer[0] == 27 && buffer[1] == 91)
			{
				printf("\nHave you pressed %s key ?\n", arrow[buffer[2] - 'A']);
			}
		}
		line[i] = '\0';
		printf("The line contains: '%s'\n", line);
		free(line);
	}
	termios_c.c_lflag &= (ICANON | ECHO);
	tcsetattr(0, 0, &termios_c);
	return (0);
}
