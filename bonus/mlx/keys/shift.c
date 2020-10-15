/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 22:58:00 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/15 23:11:03 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define XK_MISCELLANY
#include <X11/keysymdef.h>
#include "../../../sources/mlx/mlx_full.h"

void	shift(t_runtime *runtime)
{
	runtime->player.position.z = -0.9;
	release(XK_Shift_L, runtime);
}
