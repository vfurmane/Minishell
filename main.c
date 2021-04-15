#include <term.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	ft_putchar(int chr)
{
	write(1, &chr, 1);
	return ((int)chr);
}

int	main(void)
{
	struct termios	termios_c;
	int				ret;
	unsigned char	buffer[3];
	char			*cm, *DO, *UP, *LE, *RI;

	tgetent(NULL, getenv("TERM"));
	cm = tgetstr("cm", NULL);
	DO = tgetstr("DO", NULL);
	UP = tgetstr("UP", NULL);
	LE = tgetstr("LE", NULL);
	RI = tgetstr("RI", NULL);
	tcgetattr(0, &termios_c);
	termios_c.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, 0, &termios_c);
	ret = 1;
	while (ret > 0)
	{
		ret = read(0, buffer, 3);
		if (buffer[0] >= 32 && buffer[0] <= 126)
		{
			//ft_putchar(buffer);
			//tputs(tgoto(RI, 0, 1), 1, ft_putchar);
		}
		else if (buffer[0] == 127)
		{
			//tputs(tgoto(LE, 0, 1), 1, ft_putchar);
		}
		else if (buffer[0] == 27 && buffer[1] == 91)
		{
			if (buffer[2] == 'A')
				ft_putchar('^');
			else if (buffer[2] == 'B')
				ft_putchar('v');
			else if (buffer[2] == 'C')
				ft_putchar('>');
			else if (buffer[2] == 'D')
				ft_putchar('<');
		}
	}
	termios_c.c_lflag &= (ICANON | ECHO);
	tcsetattr(0, 0, &termios_c);
	return (0);
}
