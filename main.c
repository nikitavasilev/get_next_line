#include "get_next_line.h"

int		main(void)
{
	char	*line;
	int		fd;
	int		ret;
	size_t	i;

	line = NULL;
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

	i = 0;
	while ((ret = get_next_line(fd, &line)))
	{
		printf("\nCall #%zu\n", i++);
		printf("RET: %d\n", ret);
		printf("VALUE: %s\n", line);
	}

	free(line);
	close(fd);
	return (0);
}
