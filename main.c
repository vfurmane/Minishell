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

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_insert_char(char *str, int column, int chr)
{
	int	i;

	i = ft_strlen(&str[column]) + 1;
	while (--i >= 0)
		str[column + i + 1] = str[column + i];
	str[column] = chr;
	return (ft_strlen(str));
}

int	ft_delete_char(char *str, int column, int chr)
{
	int	i;
	int	len;

	len = ft_strlen(&str[column]) + 1;
	column--;
	i = -1;
	while (++i < len)
		str[column + i] = str[column + i + 1];
	return (ft_strlen(str));
}

int	main(void)
{
	struct termios	termios_c;
	int				ret;
	int				i;
	int				j;
	int				column;
	char			*line;
	unsigned char	buffer[3];
	char			*cm, *sc, *rc, *ce, *DO, *UP, *LE, *RI;
	char			*arrow[4] = {	"UP",
		"DOWN",
		"RIGHT",
		"LEFT"};

	tgetent(NULL, getenv("TERM"));
	cm = tgetstr("cm", NULL);
	sc = tgetstr("sc", NULL);
	rc = tgetstr("rc", NULL);
	ce = tgetstr("ce", NULL);
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
		column = 0;
		line = calloc(sizeof(*line), ARG_MAX + 1); /* forbidden */
		while (ret > 0 && i < ARG_MAX)
		{
			ret = read(0, buffer, 3);
			if (buffer[0] == 4)
				return (0); /* break the while here */
			else if (buffer[0] >= 32 && buffer[0] <= 126)
			{
				i = ft_insert_char(line, column, buffer[0]); /* Can be replaced with a memmove */
				column++;
				ft_putchar(buffer[0]);
			}
			else if (buffer[0] == 127 && column > 0)
			{
				i = ft_delete_char(line, column, buffer[0]); /* Can be replaced with a memmove */
				column--;
				tputs(ce, 1, ft_putchar);
				tputs(tgoto(LE, 0, 0), 1, ft_putchar);
				ft_putchar(' ');
				tputs(tgoto(LE, 0, 0), 1, ft_putchar);
			}
			else if (buffer[0] == '\n')
			{
				ft_putchar('\n');
				ret = 0;
				break ;
			}
			else if (buffer[0] == 27 && buffer[1] == 91)
			{
				if (buffer[2] == 'D' && column > 0)
				{
					tputs(tgoto(LE, 0, 0), 1, ft_putchar);
					column--;
				}
				else if (buffer[2] == 'C' && column < i)
				{
					tputs(tgoto(RI, 0, 0), 1, ft_putchar);
					column++;
				}
			}
			j = column;
			tputs(sc, 1, ft_putchar);
			while (j < i)
			{
				ft_putchar(line[j++]);
			}
			tputs(rc, 1, ft_putchar);
		}
		line[i] = '\0';
		printf("The line contains: '%s'\n", line);
		free(line);
	}
	termios_c.c_lflag &= (ICANON | ECHO);
	tcsetattr(0, 0, &termios_c);
	return (0);
}
