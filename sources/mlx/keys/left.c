/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 19:43:08 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/06 21:46:57 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx1.h"

void	left(t_runtime *runtime)
{
	runtime->player.degree -= (float)100 / 2 / MAX_FPS;
	if ((char)runtime->player.degree < 0)
		runtime->player.degree += 360;
}