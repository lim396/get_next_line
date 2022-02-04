/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shongou <shongou@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 19:11:05 by shongou           #+#    #+#             */
/*   Updated: 2022/02/03 19:11:08 by shongou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			return ((char *)s);
		s++;
	}
	if (find_c == '\0')
		pos_c = (char *)s;
	return (pos_c);
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
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s1)
{
	char	*cpy_head;

	cpy_head = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!cpy_head)
		return (NULL);
	cpy_head = ft_strcpy(cpy_head, s1);
	return (cpy_head);
}

bool	null_check(char **checked, char **released)
{
	if (!*checked)
	{
		free(*checked);
		*checked = NULL;
		free(*released);
		*released = NULL;
		return (true);
	}
	return (false);
}
