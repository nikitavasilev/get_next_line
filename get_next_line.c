/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvasilev <nvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 14:34:10 by nvasilev          #+#    #+#             */
/*   Updated: 2021/01/22 16:22:35 by nvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*ft_strcpy(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = src[i];
	return (dest);
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

char	*check_remainder(char *remainder, char **line)
{
	char	*p_newline;

	p_newline = NULL;
	if (remainder)
	{
		if ((p_newline = ft_strchr(remainder, '\n')))
		{
			*p_newline = '\0';
			*line = ft_strdup(remainder);
			ft_strcpy(remainder, ++p_newline);
		}
		else
		{
			*line = ft_strdup(remainder);
			ft_bzero(remainder, ft_strlen(remainder));
		}
	}
	else
	{
		if (!(*line = malloc(1)))
			return (0);
		line[0][0] = '\0';
	}
	return (p_newline);
}

int		get_next_line(int fd, char **line)
{
	static char	*remainder;
	char		buf[BUFFER_SIZE + 1];
	int			nb_bytes_read;
	char		*p_newline;
	char		*tmp;

	if (!line || !BUFFER_SIZE)
		return (-1);
	if (remainder && remainder[1] == '\n')
	{
		free(*line);
		return (1);
	}
	p_newline = check_remainder(remainder, line);
	while (!p_newline && (nb_bytes_read = read(fd, buf, BUFFER_SIZE)))
	{
		buf[nb_bytes_read] = '\0';
		if ((p_newline = ft_strchr(buf, '\n')))
		{
			*p_newline = '\0';
			p_newline++;
			remainder = ft_strdup(p_newline);
		}
		tmp = *line;
		*line = ft_strjoin(*line, buf);
		free(tmp);
	}
	// if (!ft_strlen(*line) && !nb_bytes_read)
	// 	free(remainder);
	return (nb_bytes_read || ft_strlen(remainder) || ft_strlen(*line) ? 1 : 0);
}
