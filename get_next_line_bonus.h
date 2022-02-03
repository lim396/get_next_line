/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shongou <shongou@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 19:11:27 by shongou           #+#    #+#             */
/*   Updated: 2022/02/03 19:11:29 by shongou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

# define FD_MAX 256

size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strdup(const char *s1);
bool	null_check(char **checked, char **released);
char	*get_next_line(int fd);

#endif
