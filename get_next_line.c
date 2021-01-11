/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvasilev <nvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 00:37:56 by nvasilev          #+#    #+#             */
/*   Updated: 2021/01/10 20:22:55 by nvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*copy;

	if (!(copy = malloc(ft_strlen(s1) + 1)))
		return (0);
	i = 0;
	while (s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = s1[i];
	return (copy);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;

	if (!s1 || !s2)
		return (0);
	if (!(str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (0);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		str[i + ft_strlen(s1)] = s2[i];
		i++;
	}
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (str);
}

char	*ft_strnew(size_t size)
{
	char *str;

	str = (char *)malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	while (size > 0)
		str[size--] = '\0';
	str[0] = '\0';
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (*s == c)
		return ((char *)s);
	return (0);
}

int		get_next_line(int fd, char **line)
{
	char	buf[BUFFER_SIZE + 1];
	int		byte_was_read;
	char	*p_n;
	int		flag;
	static char *remainder;

	flag = 1;
	if (remainder)
		*line = ft_strdup(remainder);
	else
		*line = ft_strnew(1);
	while (flag && (byte_was_read = read(fd, buf, BUFFER_SIZE)))
	{
		if ((p_n = ft_strchr(buf, '\n')))
		{
			*p_n = '\0';
			flag = 0;
			p_n++;
			remainder = ft_strdup(p_n);
		}
		buf[byte_was_read] = '\0';
		*line = ft_strjoin(*line, buf);
	}
	return (0);
}

int		main(void)
{
	char	*line;
	int		fd;

	fd = open("file.txt", O_RDONLY);
	get_next_line(fd, &line);
	printf("%s\n", line);
//	get_next_line(fd, &line);
//	printf("%s\n", line);

	return (0);
}
