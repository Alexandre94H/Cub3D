/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   down.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 22:31:43 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/15 22:50:42 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../sources/mlx/mlx1.h"

void	down(t_runtime *runtime)
{
	runtime->player.pitch -= (float)5 / MAX_FPS;
	if (runtime->player.pitch < -1)
		runtime->player.pitch = -1;
}
