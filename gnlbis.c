#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

typedef struct s_buffer
{
	int		size;
	char	content[BUFFER_SIZE + 1];
}			t_buffer;

char	*join_and_realloc(char *s, char *buf, int size);
int		find_char_index(char *str, char c);
int		get_next_line(int fd, char **line);

#endif

static int	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static char	*ft_realloc(char *str, int len)
{
	char	*new;
	int		i;

	if (len < ft_strlen(str))
		return (NULL);
	new = malloc(len * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (str[i] && i < len)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	free(str);
	return (new);
}

char	*join_and_realloc(char *s, char *buf, int size)
{
	int		i;
	int		j;
	int		n;

	n = ft_strlen(s);
	j = n + size + 1;
	s = ft_realloc(s, j);
	if (!s)
		return (NULL);
	i = 0;
	j = n;
	while (i < size)
	{
		s[j] = buf[i];
		i++;
		j++;
	}
	s[j] = '\0';
	return (s);
}

int	find_char_index(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static int	check_errors(int fd, char **line, int size, int is_start)
{
	if (BUFFER_SIZE <= 0)
		return (0);
	if (is_start)
		*line = malloc(sizeof(char));
	if (!(*line))
		return (0);
	if (size < 0 || fd < 0)
	{
		free(*line);
		*line = 0;
		return (0);
	}
	if (is_start)
		(*line)[0] = '\0';
	return (1);
}

static int	maj_buffer(char *buf, int i)
{
	int		j;

	j = 0;
	while (j < BUFFER_SIZE - i)
	{
		buf[j] = buf[i + 1 + j];
		j++;
	}
	i = j;
	while (j <= BUFFER_SIZE)
	{
		buf[j] = '\0';
		j++;
	}
	return (i);
}

static int	index_pos(int size)
{
	if (size < 0)
		return (0);
	return (size);
}

int	get_next_line(int fd, char **line)
{
	static t_buffer	buff;
	int				i;

	if (!line || !check_errors(fd, line, 1, 1))
		return (-1);
	if (buff.size <= 0)
	{
		buff.size = read(fd, buff.content, BUFFER_SIZE);
		buff.content[index_pos(buff.size)] = '\0';
	}
	while (buff.size > 0)
	{
		i = find_char_index(buff.content, '\n');
		if (i >= 0)
		{
			*line = join_and_realloc(*line, buff.content, i);
			buff.size = maj_buffer(buff.content, i);
			return (check_errors(fd, line, 1, 0));
		}
		*line = join_and_realloc(*line, buff.content, BUFFER_SIZE + 1);
		buff.size = read(fd, buff.content, BUFFER_SIZE);
		buff.content[index_pos(buff.size)] = '\0';
	}
	return (check_errors(fd, line, buff.size, 0) - 1);
}

int		main(void)
{
	char	*line;
	int		fd;

	fd = open("file.txt", O_RDONLY);
	printf("%d\n", get_next_line(fd, &line));
	printf("%s\n", line);
	printf("%d\n", get_next_line(fd, &line));
	printf("%s\n", line);
	printf("%d\n", get_next_line(fd, &line));
	printf("%s\n", line);
	printf("%d\n", get_next_line(fd, &line));
	printf("%s\n", line);
	printf("%d\n", get_next_line(fd, &line));
	printf("%s\n", line);
//	while (get_next_line(fd, &line))
//		printf("%s\n", line);
	free(line);

	close(fd);
	return (0);
}
