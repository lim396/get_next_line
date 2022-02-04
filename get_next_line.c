/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shongou <shongou@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 19:10:32 by shongou           #+#    #+#             */
/*   Updated: 2022/02/03 19:10:38 by shongou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	searched_len(const char *s, int c)
{
	char	find_c;
	size_t	i;

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

static char	*strnappend(char *s1, char *s2, size_t n)
{
	char	*ret_arr;
	size_t	i;
	size_t	j;

	if (!*s1 && !*s2)
		return (NULL);
	i = 0;
	j = 0;
	ret_arr = (char *)malloc((ft_strlen(s1) + n + 1) * sizeof(char));
	if (!ret_arr)
		return (NULL);
	while (s1[i])
	{
		ret_arr[i] = s1[i];
		i++;
	}
	while (s2[j] && n > j)
		ret_arr[i++] = s2[j++];
	ret_arr[i] = '\0';
	return (ret_arr);
}

static char	*save_after_newline(char **buf, ssize_t new_line_pos, char **line)
{
	char	*save;

	if (!ft_strchr(*line, '\n'))
	{
		free(*buf);
		*buf = NULL;
		return (NULL);
	}
	save = ft_strdup(*buf + new_line_pos + 1);
	if (!save)
	{
		free(*buf);
		*buf = NULL;
		free(*line);
		*line = NULL;
		return (NULL);
	}
	free(*buf);
	*buf = NULL;
	return (save);
}

static char	*read_and_throw(int fd, char *buf, char **save_fd)
{
	ssize_t	read_byts;
	char	*tmp;

	while (!ft_strchr(*save_fd, '\n'))
	{
		read_byts = read(fd, buf, BUFFER_SIZE);
		if (read_byts < 0)
		{
			free(*save_fd);
			return (NULL);
		}
		if (read_byts == 0)
			break ;
		buf[read_byts] = '\0';
		tmp = *save_fd;
		if (*save_fd)
			*save_fd = strnappend(*save_fd, buf, read_byts);
		else
			*save_fd = ft_strdup(buf);
		free(tmp);
		tmp = NULL;
		if (!save_fd)
			return (NULL);
	}
	return (*save_fd);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;
	char		*buf;
	size_t		newline_pos;
	char		*tmp;

	if (fd < 0 || fd > FD_MAX - 1 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(((size_t)BUFFER_SIZE + 1u) * sizeof(char));
	line = ft_strdup("");
	if (null_check(&buf, &line) || null_check(&line, &buf))
		return (NULL);
	save = read_and_throw(fd, buf, &save);
	free(buf);
	if (null_check(&save, &line))
		return (NULL);
	newline_pos = searched_len(save, '\n');
	tmp = line;
	line = strnappend(line, save, newline_pos + 1);
	free(tmp);
	if (null_check(&line, &save))
		return (NULL);
	save = save_after_newline(&save, newline_pos, &line);
	return (line);
}
