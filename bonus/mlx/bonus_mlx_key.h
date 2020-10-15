/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_mlx_key.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 22:21:44 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/15 23:00:50 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_MLX_KEY_H
# define BONUS_MLX_KEY_H

#include "../../sources/mlx/mlx_key.h"

void	up(t_runtime *runtime);
void	down(t_runtime *runtime);
void	alt(t_runtime *runtime);
void	shift(t_runtime *runtime);

t_key	g_key_board[] = {
	{XK_w, &w, -1},
	{XK_s, &s, -1},
	{XK_a, &a, -1},
	{XK_d, &d, -1},
	{XK_Left, &left, -1},
	{XK_Right, &right, -1},
	{XK_F2, &f2, -1},
	{XK_Escape, &esc, -1},
	{XK_Up, &up, -1},
	{XK_Down, &down, -1},
	{XK_Alt_L, &alt, -1},
	{XK_Shift_L, &shift, -1},
	{0, 0, 0}
};

#endif