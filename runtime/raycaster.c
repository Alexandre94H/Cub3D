/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 19:38:38 by ahallain          #+#    #+#             */
/*   Updated: 2020/05/07 22:24:39 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"
#define __USE_MISC
#include <math.h>

t_ajust	ft_ajust(t_player player)
{
	float	degree;

	degree = player.degree * M_PI / 180;
	return ((t_ajust) {player.position, {
		sin(degree),
		-1 * cos(degree)
	}, player.degree});
}

float	ft_abs(float nbr)
{
	if (nbr < 1)
		nbr *= -1;
	return (nbr);
}

t_ray	ft_load_ray(float cameraX, t_ajust ajust)
{
	t_ray	ray;

	ray = (t_ray) {{
		(int) ajust.position.x,
		(int) ajust.position.y
	}, {
		sin((ajust.degree + FOV * cameraX) * M_PI / 180),
		-1 * cos((ajust.degree + FOV * cameraX) * M_PI / 180)
	}, {0, 0}, {0, 0}, {0, 0}};
	ray.delta = (t_position) {
		ft_abs(1 / ray.direction.x),
		ft_abs(1 / ray.direction.y)
	};
	if (ray.direction.x < 0)
	{
		ray.step.x = -1;
		ray.side.x = (ajust.position.x - ray.position.x) * ray.delta.x;
	}
	else
	{
		ray.step.x = 1;
		ray.side.x = (ray.position.x - ajust.position.x + 1) * ray.delta.x;
	}
	if (ray.direction.y < 0)
	{
		ray.step.y = -1;
		ray.side.y = (ajust.position.y - ray.position.y) * ray.delta.y;
	}
	else
	{
		ray.step.y = 1;
		ray.side.y = (ray.position.y - ajust.position.y + 1) * ray.delta.y;
	}
	return (ray);
}

float	ft_distance(float cameraX, t_ajust ajust, char **map)
{
	t_ray	ray;
	int		side;

	ray = ft_load_ray(cameraX, ajust);
	while (1)
	{
		if (ray.side.x < ray.side.y)
		{
			ray.side.x += ray.delta.x;
			ray.position.x += ray.step.x;
			side = 0;
		}
		else
		{
			ray.side.y += ray.delta.y;
			ray.position.y += ray.step.y;
			side = 1;
		}
		if (map[(int)ray.position.y][(int)ray.position.x] == '1')
			break;
	}
	if (!side)
		return ((ray.position.x - ajust.position.x + (1 - ray.step.x) / 2) / ray.direction.x);
	return ((ray.position.y - ajust.position.y + (1 - ray.step.y) / 2) / ray.direction.y);
}