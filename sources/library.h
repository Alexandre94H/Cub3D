/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   library.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 21:50:50 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/20 13:52:38 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBRARY_H
# define LIBRARY_H

# include <stdbool.h>
# include "../libraries/get_next_line/get_next_line.h"

typedef struct	s_list
{
	void*	items[255];
}				t_list;

void			ft_putchar_fd(const char c, const int fd);
void			ft_putstr_fd(const char *str, const int fd);
void			ft_putnbr_fd(int nbr, const int fd);
int				ft_atoi(const char *str);
void			*ft_strdup(const char *str, const size_t length);
short			ft_array_add(void ***list, const void *item);
void			ft_array_remove(void ***list, const unsigned short index);
char			*ft_itoa(const int n);
bool			ft_equals(const char *str, const char *str1);
char			*ft_tolower(char *str);
int				ft_strstr(const char *str, const char *chunk);
#endif
