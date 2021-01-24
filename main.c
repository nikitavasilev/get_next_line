#include "get_next_line.h"

int		main(void)
{
	char	*line;
	int		fd;

	fd = open("file.txt", O_RDONLY);
	// printf("%d\n", get_next_line(fd, &line));
	// printf("%s\n", line);
	// printf("%d\n", get_next_line(fd, &line));
	// printf("%s\n", line);
	// printf("%d\n", get_next_line(fd, &line));
	// printf("%s\n", line);
	// printf("%d\n", get_next_line(fd, &line));
	// printf("%s\n", line);
	// printf("%d\n", get_next_line(fd, &line));
	// printf("%s\n", line);
	// printf("%d\n", get_next_line(fd, &line));
	// printf("%s\n", line);
	while (get_next_line(fd, &line))
		printf("%s\n", line);

	free(line);
	close(fd);
	return (0);
}
