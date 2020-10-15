/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 22:45:11 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/15 23:10:57 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define XK_MISCELLANY
#include <X11/keysymdef.h>
#include "../../../sources/mlx/mlx_full.h"

void	alt(t_runtime *runtime)
{
	runtime->player.position.z = 0.9;
	release(XK_Alt_L, runtime);
}
