/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_key.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 22:05:55 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/18 23:35:14 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_KEY_H
# define MLX_KEY_H

# define XK_LATIN1
# define XK_MISCELLANY
# include <X11/keysymdef.h>
# include <stdbool.h>
# include "mlx1.h"
# include "keys.h"

# if BONUS
#  include "../../bonus/mlx/bonus_mlx_key.h"
# endif

# if !BONUS

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
