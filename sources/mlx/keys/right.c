/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 19:44:12 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/14 22:15:56 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx1.h"

void	right(t_runtime *runtime)
{
	runtime->player.degree += (float)100 / MAX_FPS;
	if (runtime->player.degree > 360)
		runtime->player.degree -= 360;
}
