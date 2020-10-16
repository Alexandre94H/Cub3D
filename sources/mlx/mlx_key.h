/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_key.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 22:05:55 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/16 19:39:39 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_KEY_H
# define MLX_KEY_H

# define XK_LATIN1
# define XK_MISCELLANY
# include <X11/keysymdef.h>
# include <stdbool.h>
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


# if BONUS
	#  include "../../bonus/mlx/bonus_mlx_key.h"
# else
	t_key	g_key_board[] = {
		{XK_w, &w, -1, false},
		{XK_s, &s, -1, false},
		{XK_a, &a, -1, false},
		{XK_d, &d, -1, false},
		{XK_Left, &left, -1, false},
		{XK_Right, &right, -1, false},
		{XK_F2, &f2, -1, false},
		{XK_Escape, &esc, -1, false},
		{0, 0, 0, 0}
	};
# endif
#endif
