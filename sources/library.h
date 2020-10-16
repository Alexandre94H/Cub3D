/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   library.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 21:50:50 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/16 10:49:14 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBRARY_H
# define LIBRARY_H

# include "../libraries/get_next_line/get_next_line.h"

typedef struct	s_list
{
	void*	items[255];
}				t_list;

void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *str, int fd);
void			ft_putnbr_fd(int nbr, int fd);
int				ft_atoi(char *str);
void			*ft_strdup(char *str, size_t length);
short			array_add(void ***list, void *item);
void			array_remove(void ***list, unsigned short index);
char			*ft_itoa(int n);

#endif
