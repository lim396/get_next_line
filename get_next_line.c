#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
//#include <errno.h>
#include <bool.h>
#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;
	
	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	char	*pos_c;
	char	find_c;

	if (!s)
		return (NULL);
	pos_c = NULL;
	find_c = (char)c;
	while (*s)
	{
		if (*s == find_c)
			return (char *)s;
		s++;
	}
	if (find_c == '\0')
		pos_c = (char *)s;
	return (pos_c);
}

ssize_t searched_len(const char *s, int c)
{
	char	find_c;
	ssize_t i;

	if (!s)
		return (0);
	find_c = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == find_c)
			return (i);
		i++;
	}
	return (i);
}

char *strnappend(char *s1, char *s2, size_t n)
{
	size_t	new_arr_size;
	char	*arr_head;
	char	*tmp;
	
	if (!*s1 && !*s2)
		return (NULL);
	new_arr_size = ft_strlen(s1) + n + 1;
	arr_head = (char *)malloc(new_arr_size + 1);
	if (!arr_head)
		return (NULL);
	tmp = arr_head;
	while (*s1)
		*tmp++ = *s1++;
	while (*s2 && n--)
		*tmp++ = *s2++;
	*tmp = '\0';
	return (arr_head);
}

char *ft_strcpy(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char *ft_strdup(const char *s1)
{
	char	*cpy_head;

	cpy_head = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!cpy_head)
		return (NULL);
	cpy_head = ft_strcpy(cpy_head, s1);
	return (cpy_head);
}

char *save_after_newline(char *buf, ssize_t new_line_pos, char *line)
{
	char	*save;

	if (!ft_strchr(line, '\n'))
	{
		free(buf);
		buf = NULL;
		return (NULL);
	}
	save = ft_strdup(buf + new_line_pos + 1);
	if (!save)
	{
		free(buf);
		buf = NULL;
		free(line);
		line = NULL;
		return (NULL);
	}
	free(buf);
	buf = NULL;
	return (save);
}

char	*read_and_throw(int fd, char *buf, char *save_fd)
{
	ssize_t	read_byts;
	char	*tmp;
	
	while (!ft_strchr(save_fd, '\n'))
	{	
		read_byts = read(fd, buf, BUFFER_SIZE);
		if (read_byts < 0)
		{
			free(save_fd);
			return (NULL);
		}
		if (read_byts == 0)
			break ;
		buf[read_byts] = '\0';
		tmp = save_fd;
		if (save_fd)
			save_fd = strnappend(save_fd, buf, read_byts);
		else
			save_fd = ft_strdup(buf);
		free(tmp);
		tmp = NULL;
		if (!save_fd)
			return (NULL);
	}
	return (save_fd);
}

bool	null_check(char *checked, char *released)
{
	if (!checked)
	{
		free(save);
		save = NULL;
		free(line);
		line = NULL;
		return (true);		
	}
	return (false);
}

char	*get_next_line(int fd)
{
	static char	*save[257];
	char		*line;
	char		*buf;
	size_t		newline_pos;
	char		*tmp;

	if (fd < 0 || 256 < fd || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(BUFFER_SIZE + 1);m
	if (!buf)
		return (NULL);
	line = ft_strdup("");
	save[fd] = read_and_throw(fd, buf, save[fd]);
	free(buf);
	if (null_check(save[fd], line))
		return (NULL);
	newline_pos = searched_len(save[fd], '\n');
	tmp = line;
	line = strnappend(line, save[fd], newline_pos + 1);
	free(tmp);
	if (null_check(line, save[fd]))
		return (NULL);
	save[fd] = save_after_newline(save[fd], newline_pos, line);
	return (line);
}
