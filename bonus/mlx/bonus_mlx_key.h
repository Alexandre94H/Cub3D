/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_mlx_key.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 22:21:44 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/16 19:24:25 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_MLX_KEY_H
# define BONUS_MLX_KEY_H

# include "../../sources/mlx/mlx_key.h"

void	up(t_runtime *runtime);
void	down(t_runtime *runtime);
void	alt(t_runtime *runtime);
void	shift(t_runtime *runtime);

t_key	g_key_board[] = {
	{XK_w, &w, -1, false},
	{XK_s, &s, -1, false},
	{XK_a, &a, -1, false},
	{XK_d, &d, -1, false},
	{XK_Left, &left, -1, false},
	{XK_Right, &right, -1, false},
	{XK_F2, &f2, -1, false},
	{XK_Escape, &esc, -1, false},
	{XK_Up, &up, -1, false},
	{XK_Down, &down, -1, false},
	{XK_Alt_L, &alt, -1, true},
	{XK_Shift_L, &shift, -1, false},
	{0, 0, 0, 0}
};
#endif
