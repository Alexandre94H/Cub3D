/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 05:56:08 by ahallain          #+#    #+#             */
/*   Updated: 2020/06/18 14:40:52 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#define __USE_MISC
#include <math.h>

t_ray		ft_init_ray(float degree)
{
	t_ray	ray;

	ray = (t_ray) {{
		sin(degree * M_PI / 180),
		-1 * cos(degree * M_PI / 180)
	}, {
		sin((degree + FOV / 2) * M_PI / 180)
			- sin((degree - FOV / 2) * M_PI / 180),
		cos((degree - FOV / 2) * M_PI / 180)
			- cos((degree + FOV / 2) * M_PI / 180)
	}, degree};
	return (ray);
}

float		ft_abs(float nbr)
{
	if (nbr < 0)
		nbr *= -1;
	return (nbr);
}

t_caster	ft_init_caster(t_ray ray, float camerax, t_position position,
	t_position map_position)
{
	t_position	direction;
	t_caster	caster;

	direction = (t_position) {ray.direction.x + ray.plane.x * camerax,
		ray.direction.y + ray.plane.y * camerax};
	caster = (t_caster) {direction, {ft_abs(1 / direction.x),
		ft_abs(1 / direction.y)}, {0, 0}, {0, 0}};
	if (direction.x < 0)
		caster = (t_caster) {caster.direction, caster.delta,
			{(position.x - map_position.x) * caster.delta.x, 0}, {-1, 0}};
	else
		caster = (t_caster) {caster.direction, caster.delta,
			{(map_position.x - position.x + 1) * caster.delta.x, 0}, {1, 0}};
	if (direction.y < 0)
		caster = (t_caster) {caster.direction, caster.delta,
			{caster.side.x, (position.y - map_position.y)
			* caster.delta.y}, {caster.step.x, -1}};
	else
		caster = (t_caster) {caster.direction, caster.delta, {caster.side.x,
			(map_position.y - position.y + 1)
			* caster.delta.y}, {caster.step.x, 1}};
	return (caster);
}

void		ft_update_caster(t_caster *caster, t_position *map_position,
	int *side)
{
	if ((*caster).side.x < (*caster).side.y)
	{
		(*caster).side.x += (*caster).delta.x;
		(*map_position).x += (*caster).step.x;
		*side = (*caster).step.x + 1;
	}
	else
	{
		(*caster).side.y += (*caster).delta.y;
		(*map_position).y += (*caster).step.y;
		*side = (*caster).step.y + 2;
	}
}

t_calc		ft_distance(t_ray ray, float camerax, t_position position,
	char **map)
{
	t_caster	caster;
	t_position	map_position;
	int			side;
	t_calc		calc;

	map_position = (t_position){(int)position.x, (int)position.y};
	caster = ft_init_caster(ray, camerax, position, map_position);
	while (1)
	{
		ft_update_caster(&caster, &map_position, &side);
		if (map[(int)map_position.y][(int)map_position.x] == '1')
			break ;
	}
	if (side % 2)
		calc = (t_calc){((map_position.y - position.y
			+ (1 - caster.step.y) / 2) / caster.direction.y), 0, side};
	else
		calc = (t_calc){((map_position.x - position.x
			+ (1 - caster.step.x) / 2) / caster.direction.x), 0, side};
	if (side % 2)
		calc.texture_x = position.x + calc.distance * caster.direction.x;
	else
		calc.texture_x = position.y + calc.distance * caster.direction.y;
	calc.texture_x -= floor(calc.texture_x);
	return (calc);
}
