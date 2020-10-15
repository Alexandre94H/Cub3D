/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 07:32:54 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/15 22:55:08 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../mlx_full.h"

void update_wall(t_runtime *runtime, t_ray ray)
{
	for (int x = 0; x < runtime->file.resolution.width; x++)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)(runtime->file.resolution.width) - 1; //x-coordinate in camera space
		double rayDirX = ray.direction.x + ray.plan.x * cameraX;
		double rayDirY = ray.direction.y + ray.plan.y * cameraX;

		//which box of the map we're in
		int mapX = (int)(runtime->player.position.x);
		int mapY = (int)(runtime->player.position.y);

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side;	 //was a NS or a EW wall hit?

		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (runtime->player.position.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - runtime->player.position.x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (runtime->player.position.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - runtime->player.position.y) * deltaDistY;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (runtime->file.map[mapY][mapX] == '1')
				hit = 1;
		}

		//Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
		if (side == 0)
			perpWallDist = (mapX - runtime->player.position.x + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - runtime->player.position.y + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(runtime->file.resolution.height / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + runtime->file.resolution.height / 2 + runtime->player.pitch * 200 + (runtime->player.position.z * 200 / perpWallDist);
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + runtime->file.resolution.height / 2 + runtime->player.pitch * 200 + (runtime->player.position.z * 200 / perpWallDist);
		if (drawEnd >= runtime->file.resolution.height)
			drawEnd = runtime->file.resolution.height - 1;
		//texturing calculations
		//int texNum = runtime->file.map[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (side == 0)
			wallX = runtime->player.position.y + perpWallDist * rayDirY;
		else
			wallX = runtime->player.position.x + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		t_texture texture;
		if (side == 0)
			if (rayDirX < 0)
				texture = runtime->file.west;
			else
				texture = runtime->file.east;
		else if (rayDirY < 0)
			texture = runtime->file.north;
		else
			texture = runtime->file.south;

		//x coordinate on the texture
		int texX = (int)(wallX * (double)(texture.resolution.width));
		if (side == 0 && rayDirX < 0)
			texX = texture.resolution.width - texX - 1;
		if (side == 1 && rayDirY > 0)
			texX = texture.resolution.width - texX - 1;

		// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * texture.resolution.height / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - runtime->player.pitch * 200 - (runtime->player.position.z * 200 / perpWallDist) - runtime->file.resolution.height / 2 + lineHeight / 2) * step;
		for (int y = drawStart; y < drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (texture.resolution.height - 1);
			texPos += step;
			int color = texture.data[texture.resolution.height * texY + texX];
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			//if(side == 1) color = (color >> 1) & 8355711;
			runtime->mlx.data[y * runtime->file.resolution.width + x] = color;
		}
		runtime->mlx.buffer[x] = perpWallDist;
	}
}