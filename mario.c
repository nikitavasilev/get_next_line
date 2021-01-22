#include <stdlib.h>
#include <stdio.h>

void	print_chars(int height, int len, char c)
{
	while (++len < height)
		putchar(c);
}

void	print_line(int height, int line)
{
	if (height - line)
	{
		print_line(height, ++line);
		print_chars(height, height - line, ' ');
		print_chars(height + 1, line - 1, '#');
		putchar(' ');
		print_chars(height + 1, line - 1, '#');
		putchar('\n');
	}
}

int		main(int argc, char **argv)
{
	if (argc == 2 && atoi(argv[1]) > 0)
	{
		printf("\nHeight: %s\n\n", argv[1]);
		print_line(atoi(argv[1]) + 1, 1);
	}
	return (0);
}
