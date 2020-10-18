/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 23:32:50 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/18 23:35:04 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H
# include "mlx1.h"

typedef struct	s_key
{
	unsigned short	input;
	t_key_f			function;
	char			index;
	bool			one_time;
}				t_key;

void			w(t_runtime *runtime);
void			s(t_runtime *runtime);
void			a(t_runtime *runtime);
void			d(t_runtime *runtime);
void			left(t_runtime *runtime);
void			right(t_runtime *runtime);
void			f2(t_runtime *runtime);
void			esc(t_runtime *runtime);
#endif
