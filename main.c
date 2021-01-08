#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif


int	get_next_line(int fd, char **line)
{
	size_t	i;

	i = 0;
	(void)fd;
	while (*line[i] != '\n')
	{
		printf("%c", *line[i]);
		i++;
	}
	return (0);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

int	main(void)
{
	static char buffer[BUFFER_SIZE + 1];
	int	fd;
	size_t	i;
	size_t	j;
	char *str;

	ft_bzero(buffer, BUFFER_SIZE + 1);
	fd = open("file.txt", O_RDONLY);
	printf("\n%zd\n", read(fd, buffer, BUFFER_SIZE));
	//get_next_line(fd, &buffer);
	//printf("%s\n", buffer);
	i = 0;
	while (buffer[i] != '\n')
	{
		write(1, &buffer[i], 1);
		i++;
	}
	if (!(str = malloc(i + 1)))
		return (0);
	j = 0;
	while (j < i)
	{
		str[j] = buffer[j];
		j++;
	}
	str[j] = '\0';
	printf("%s\n", str);

	//printf("%zd\n", read(fd, buffer, BUFFER_SIZE));
	//printf("%s\n", buffer);

	close(fd);

	return (0);
}
