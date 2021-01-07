#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

/*
int	get_next_line(int fd, char **line)
{
	return (0);
}
*/

int	main(void)
{
	static char buffer[15];
	int	fd;

	fd = open("file.txt", O_RDONLY);
	printf("%zd\n", read(fd, buffer, BUFFER_SIZE));
	return (0);
}
