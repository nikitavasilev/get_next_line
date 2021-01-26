# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFF_SIZE
#  define BUFF_SIZE 32
# endif

size_t ft_strlen(const char *str)
{
    size_t i;
    i = 0;
    while(str[i])
        i++;
    return (i);
}
char *ft_strchr(char *str)
{
    while(*str)
    {
        if(*str == '\n')
            return (str);
        str++;
    }
    return (0);
}
char *ft_strjoin(char const *s1, char const *s2)
{
    char *str;
    char *begin;
    char const *s1begin;
    if(!s1 || !s2)
        return (0);
    if(!(str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1))))
        return (0);
    begin = str;
    s1begin = s1;
    while(*(char *)s1)
    {
        *str = *(char *)s1;
        s1++;
        str++;
    }
    while(*(char *)s2)
    {
        *str = *(char *)s2;
        s2++;
        str++;
    }
    *str = '\0';
    free((char*)s1begin);
    return (begin);
}
char    *ft_strdup(const char *s1)
{
    char    *str;
    int     i;
    i = 0;
    while (s1[i])
        i++;
    if (!(str = malloc(sizeof(char) * i + 1)))
        return (NULL);
    i = -1;
    while (s1[++i])
        str[i] = s1[i];
    str[i] = '\0';
    return (str);
}
void    update_remainder(char *str, char **remainder)
{
    char *tmp;

    if(*str)
    {
        tmp = *remainder;
        *remainder = ft_strdup(str);
        free(tmp);
    }
}
int     ft_remainder(char **remainder, char **str)
{
    char *nextline;

    if(remainder && *remainder)
    {
        printf("yes if\n");
        if((nextline = ft_strchr(*remainder)))
        {
            *nextline = '\0';
            *str = ft_strjoin(*str, *remainder);
            update_remainder(++(nextline), remainder);
            return (1);
        }
        else
		{
			*str = ft_strjoin(*str, *remainder);
            free(*remainder);
            *remainder = NULL;
		}
    }
    return (0);
}
int get_next_line(const int fd, char **line)
{
    static char *remainder;
    size_t  size;
    char buff[BUFF_SIZE+1];
    char *nextline;
    if(fd < 0 || !line || !(*line = malloc(1)))
        return (-1);
    **line = '\0';
    if(remainder)
    {
        if(ft_remainder(&remainder, line))
            return (1);
    }
    while((size = read(fd, buff, BUFF_SIZE)) > 0)
    {
        buff[size] = '\0';
        if((nextline = ft_strchr(buff)))
        {
            *nextline = '\0';
            *line = ft_strjoin(*line, buff);
            update_remainder(++(nextline), &remainder);
            return (1);
        }
        *line = ft_strjoin(*line, buff);
    }
    if(remainder && *remainder && !size)
        return (1);
    return (size);
}
int main(void)
{
    int file;
    char *str;
    file = open("file.txt", O_RDONLY);

    int i = 0;
    int result;
    while(i < 10)
    {
        result = get_next_line(file, &str);

        printf("\nresult %i: %s\n", result, str);
        free(str);
        i++;
    }
	return (0);
}
