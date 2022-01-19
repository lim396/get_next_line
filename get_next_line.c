#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <errno.h>
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

ssize_t search_len(const char *s, int c)
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
	{
		//free(s1);
		//free(s2);
		return (NULL);
	}
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
	//free(s1);
	//s1 = NULL;
	return (arr_head);
}

/*void	free_line_and_save(char *save, char *line)
{
	free(save);
	save = NULL;
	free(line);
	line = NULL;
}*/

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

	//if (!*buf)
	//{
	//	free(buf);
	//	return (NULL);
	//}
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

/*ssize_t append_save_buf(char **save, char *buf)
{
	char	*line;
	char	*tmp;
	ssize_t new_line_pos;

	new_line_pos = search_len(buf, '\n');
	if (!strchr(buf, '\n'))
		tmp = strnappend(*save, buf, new_line_pos);
	if (!tmp)
		return (-1);
	*line = tmp;
	free(tmp);
	tmp = NULL;
	if (buf[new_line_pos] == '\n')
	{
		tmp = ft_strdup(buf + new_line_pos + 1);
		if (!tmp)
			return (-1);
	}
	free(*save);
	*save = tmp;
	free(tmp);
	return (read_byts);
}*/

char	*read_and_throw(int fd, char *buf, char *save_fd)
{
	ssize_t	read_byts;
	char	*tmp;
	
	while (!ft_strchr(save_fd, '\n'))
	{	
		read_byts = read(fd, buf, BUFFER_SIZE); // cut func read_and_throw
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

int	null_check(char *checked, char *released) //bool
{
	if (!checked)
	{
		free(save);
		save = NULL;
		free(line);
		line = NULL;
		return (1);		
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*save[257]; //256?
	//ssize_t		read_byts;
	char		*line;
	char		*buf;
	size_t		newline_pos;
	char		*tmp;
	//char		*temp;

	if (fd < 0 || 256 < fd || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(BUFFER_SIZE + 1);// cut func reserve_mem
	if (!buf)
		return (NULL);
	line = ft_strdup("");
	save[fd] = read_and_throw(fd, buf, save[fd]);
	free(buf);
	//buf = NULL;
	if (null_check(save[fd], line))
		return (NULL);
	newline_pos = search_len(save[fd], '\n');
	tmp = line;
	line = strnappend(line, save[fd], newline_pos + 1);
	free(tmp);
	//tmp = NULL;
	if (null_check(line, save[fd]))
		return (NULL);
	//tmp = save[fd];
	//temp = save[fd];
	save[fd] = save_after_newline(save[fd], newline_pos, line);
	//free(temp);
	//temp = NULL;
	//if (!line)
	//	free_line_and_save(save[fd], line);
	return (line);
}
