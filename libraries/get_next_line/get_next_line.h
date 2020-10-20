/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 20:13:18 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/20 19:30:27 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# include <stddef.h>

int		ft_strcchr(const char *src, const int c);
size_t	ft_strlen(const char *src, const int c);
char	*ft_stradd(char **dst, const char *str);
char	*ft_firstchr(const char *src, const int c);
char	*ft_chrmove(char **dst, const int c);
int		get_next_line(int fd, char **line);

#endif
