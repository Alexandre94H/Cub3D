/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 07:33:06 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/15 22:55:08 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../mlx_full.h"

void update_sprite(t_runtime *runtime, t_ray ray)
{
	unsigned short length;
	/*for(int i = 0; i < numSprites; i++)
    {
      spriteOrder[i] = i;
      spriteDistance[i] = ((posX - sprite[i].x) * (posX - sprite[i].x) + (posY - sprite[i].y) * (posY - sprite[i].y)); //sqrt not taken, unneeded
    }
    sortSprites(spriteOrder, spriteDistance, numSprites);*/

	//after sorting the sprites, do the projection and draw them

	if (!runtime->player.sprites)
		return;
	length = 0;
	while (runtime->player.sprites[length])
	{
		//translate sprite position to relative to camera
		double spriteX = runtime->player.sprites[length]->position.x - runtime->player.position.x;
		double spriteY = runtime->player.sprites[length]->position.y - runtime->player.position.y;

		//transform sprite with the inverse camera matrix
		// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
		// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		// [ planeY   dirY ]                                          [ -planeY  planeX ]

		double invDet = 1.0 / (ray.plan.x * ray.direction.y - ray.direction.x * ray.plan.y); //required for correct matrix multiplication

		double transformX = invDet * (ray.direction.y * spriteX - ray.direction.x * spriteY);
		double transformY = invDet * (-ray.plan.y * spriteX + ray.plan.x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

		int spriteScreenX = (int)((runtime->file.resolution.width / 2) * (1 + transformX / transformY));

//parameters for scaling and moving the sprites
#define uDiv 1
#define vDiv 1
#define vMove 0.0
		int vMoveScreen = (int)(vMove / transformY) + runtime->player.pitch * 200 + runtime->player.position.z * 200 / transformY;

		//calculate height of the sprite on screen
		int spriteHeight = abs((int)(runtime->file.resolution.height / (transformY))) / vDiv; //using "transformY" instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + runtime->file.resolution.height / 2 + vMoveScreen;
		if (drawStartY < 0)
			drawStartY = 0;
		int drawEndY = spriteHeight / 2 + runtime->file.resolution.height / 2 + vMoveScreen;
		if (drawEndY >= runtime->file.resolution.height)
			drawEndY = runtime->file.resolution.height - 1;

		//calculate width of the sprite
		int spriteWidth = abs((int)(runtime->file.resolution.height / (transformY))) / uDiv;
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX < 0)
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= runtime->file.resolution.width)
			drawEndX = runtime->file.resolution.width - 1;

		//loop through every vertical stripe of the sprite on screen
		for (int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * runtime->file.sprites[runtime->player.sprites[length]->index]->resolution.width / spriteWidth) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if (transformY > 0 && stripe > 0 && stripe < runtime->file.resolution.width && transformY < runtime->mlx.buffer[stripe])
				for (int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
				{
					int d = (y - vMoveScreen) * 256 - runtime->file.resolution.height * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
					int texY = ((d * runtime->file.sprites[runtime->player.sprites[length]->index]->resolution.height) / spriteHeight) / 256;
					int color = runtime->file.sprites[runtime->player.sprites[length]->index]->data[runtime->file.sprites[runtime->player.sprites[length]->index]->resolution.width * texY + texX]; //get current color from the texture
					if ((color & 0x00FFFFFF) != 0)
						runtime->mlx.data[y * runtime->file.resolution.width + stripe] = color; //paint pixel if it isn't black, black is the invisible color
				}
		}
		length++;
	}
}