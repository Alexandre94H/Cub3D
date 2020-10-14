/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 11:01:06 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/11 18:42:59 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define __USE_MISC
#include <math.h>
#include <mlx.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "mlx_full.h"

double ZBuffer[10000];

void	update_floor(t_runtime *runtime, t_ray ray)
{
	for(int y = 0; y < runtime->file.resolution.height; ++y)
    {
      // whether this section is floor or ceiling
      bool is_floor = y > runtime->file.resolution.height / 2 + runtime->player.pitch;

      // rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
      float rayDirX0 = ray.direction.x - ray.plan.x;
      float rayDirY0 = ray.direction.y - ray.plan.y;
      float rayDirX1 = ray.direction.x + ray.plan.x;
      float rayDirY1 = ray.direction.y + ray.plan.y;

      // Current y position compared to the center of the screen (the horizon)
      int p = is_floor ? (y - runtime->file.resolution.height / 2 - runtime->player.pitch) : (runtime->file.resolution.height / 2 - y + runtime->player.pitch);

      // Vertical position of the camera.
      // NOTE: with 0.5, it's exactly in the center between floor and ceiling,
      // matching also how the walls are being raycasted. For different values
      // than 0.5, a separate loop must be done for ceiling and floor since
      // they're no longer symmetrical.
      float camZ = is_floor ? (0.5 * runtime->file.resolution.height + runtime->player.position.z) : (0.5 * runtime->file.resolution.height - runtime->player.position.z);

      // Horizontal distance from the camera to the floor for the current row.
      // 0.5 is the z position exactly in the middle between floor and ceiling.
      // NOTE: this is affine texture mapping, which is not perspective correct
      // except for perfectly horizontal and vertical surfaces like the floor.
      // NOTE: this formula is explained as follows: The camera ray goes through
      // the following two points: the camera itself, which is at a certain
      // height (posZ), and a point in front of the camera (through an imagined
      // vertical plane containing the screen pixels) with horizontal distance
      // 1 from the camera, and vertical position p lower than posZ (posZ - p). When going
      // through that point, the line has vertically traveled by p units and
      // horizontally by 1 unit. To hit the floor, it instead needs to travel by
      // posZ units. It will travel the same ratio horizontally. The ratio was
      // 1 / p for going through the camera plane, so to go posZ times farther
      // to reach the floor, we get that the total horizontal distance is posZ / p.
      float rowDistance = camZ / p;

      // calculate the real world step vector we have to add for each x (parallel to camera plane)
      // adding step by step avoids multiplications with a weight in the inner loop
      float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / runtime->file.resolution.width;
      float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / runtime->file.resolution.width;

      // real world coordinates of the leftmost column. This will be updated as we step to the right.
      float floorX = runtime->player.position.x + rowDistance * rayDirX0;
      float floorY = runtime->player.position.y + rowDistance * rayDirY0;

      for(int x = 0; x < runtime->file.resolution.width; ++x)
      {
        // the cell coord is simply got from the integer parts of floorX and floorY
        int cellX = (int)(floorX);
        int cellY = (int)(floorY);

        // get the texture coordinate from the fractional part
        double tx = (floorX - cellX);
        double ty = (floorY - cellY);

        floorX += floorStepX;
        floorY += floorStepY;

        // choose texture and draw the pixel
        int color;


        if(is_floor) {
          // floor
          color = runtime->file.floor.data[runtime->file.floor.resolution.width * ((int)(runtime->file.floor.resolution.height * ty) & (runtime->file.floor.resolution.height - 1)) + ((int)(runtime->file.floor.resolution.width * tx) & (runtime->file.floor.resolution.width - 1))];
          //color = (color >> 1) & 8355711; // make a bit darker
        } else {
          //ceiling
		  color = runtime->file.ceil.data[runtime->file.ceil.resolution.width * ((int)(runtime->file.ceil.resolution.height * ty) & (runtime->file.ceil.resolution.height - 1)) + ((int)(runtime->file.ceil.resolution.width * tx) & (runtime->file.ceil.resolution.width - 1))];
          //color = (color >> 1) & 8355711; // make a bit darker
        }
          runtime->mlx.data[y * runtime->file.resolution.width + x] = color;
	  }
    }
}

void update_wall(t_runtime *runtime, t_ray ray)
{
	for(int x = 0; x < runtime->file.resolution.width; x++)
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
      int side; //was a NS or a EW wall hit?

      //calculate step and initial sideDist
      if(rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (runtime->player.position.x - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - runtime->player.position.x) * deltaDistX;
      }
      if(rayDirY < 0)
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
        if(sideDistX < sideDistY)
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
        if(runtime->file.map[mapY][mapX] == '1') hit = 1;
      }

      //Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
      if(side == 0) perpWallDist = (mapX - runtime->player.position.x + (1 - stepX) / 2) / rayDirX;
      else          perpWallDist = (mapY - runtime->player.position.y + (1 - stepY) / 2) / rayDirY;

      //Calculate height of line to draw on screen
      int lineHeight = (int)(runtime->file.resolution.height / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + runtime->file.resolution.height / 2 + runtime->player.pitch + (runtime->player.position.z / perpWallDist);
      if(drawStart < 0) drawStart = 0;
      int drawEnd = lineHeight / 2 + runtime->file.resolution.height / 2 + runtime->player.pitch + (runtime->player.position.z / perpWallDist);
      if(drawEnd >= runtime->file.resolution.height) drawEnd = runtime->file.resolution.height - 1;
      //texturing calculations
      //int texNum = runtime->file.map[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

      //calculate value of wallX
      double wallX; //where exactly the wall was hit
      if(side == 0) wallX = runtime->player.position.y + perpWallDist * rayDirY;
      else          wallX = runtime->player.position.x + perpWallDist * rayDirX;
      wallX -= floor((wallX));

	t_texture texture;
	if (side == 0)
		if (rayDirX < 0)
			texture = runtime->file.west;
		else
			texture = runtime->file.east;
	else
		if (rayDirY < 0)
			texture = runtime->file.north;
		else
			texture = runtime->file.south;

      //x coordinate on the texture
      int texX = (int)(wallX * (double)(texture.resolution.width));
      if(side == 0 && rayDirX < 0) texX = texture.resolution.width - texX - 1;
      if(side == 1 && rayDirY > 0) texX = texture.resolution.width - texX - 1;

      // TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
      // How much to increase the texture coordinate per screen pixel
      double step = 1.0 * texture.resolution.height / lineHeight;
      // Starting texture coordinate
      double texPos = (drawStart - runtime->player.pitch - (runtime->player.position.z / perpWallDist) - runtime->file.resolution.height / 2 + lineHeight / 2) * step;
	  for(int y = drawStart; y < drawEnd; y++)
      {
        // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
        int texY = (int)texPos & (texture.resolution.height - 1);
        texPos += step;
        int color = texture.data[texture.resolution.height * texY + texX];
        //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
        //if(side == 1) color = (color >> 1) & 8355711;
        runtime->mlx.data[y * runtime->file.resolution.width + x] = color;
      }
	  ZBuffer[x] = perpWallDist;
	}
}

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
      int vMoveScreen = (int)(vMove / transformY) + runtime->player.pitch + runtime->player.position.z / transformY;

      //calculate height of the sprite on screen
      int spriteHeight = abs((int)(runtime->file.resolution.height / (transformY))) / vDiv; //using "transformY" instead of the real distance prevents fisheye
      //calculate lowest and highest pixel to fill in current stripe
      int drawStartY = -spriteHeight / 2 + runtime->file.resolution.height / 2 + vMoveScreen;
      if(drawStartY < 0) drawStartY = 0;
      int drawEndY = spriteHeight / 2 + runtime->file.resolution.height / 2 + vMoveScreen;
      if(drawEndY >= runtime->file.resolution.height) drawEndY = runtime->file.resolution.height - 1;

      //calculate width of the sprite
      int spriteWidth = abs((int)(runtime->file.resolution.height / (transformY))) / uDiv;
      int drawStartX = -spriteWidth / 2 + spriteScreenX;
      if(drawStartX < 0) drawStartX = 0;
      int drawEndX = spriteWidth / 2 + spriteScreenX;
      if(drawEndX >= runtime->file.resolution.width) drawEndX = runtime->file.resolution.width - 1;

      //loop through every vertical stripe of the sprite on screen
      for(int stripe = drawStartX; stripe < drawEndX; stripe++)
      {
        int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * runtime->file.sprites[runtime->player.sprites[length]->index]->resolution.width / spriteWidth) / 256;
        //the conditions in the if are:
        //1) it's in front of camera plane so you don't see things behind you
        //2) it's on the screen (left)
        //3) it's on the screen (right)
        //4) ZBuffer, with perpendicular distance
        if(transformY > 0 && stripe > 0 && stripe < runtime->file.resolution.width && transformY < ZBuffer[stripe])
        for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
        {
          int d = (y-vMoveScreen) * 256 - runtime->file.resolution.height * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
          int texY = ((d * runtime->file.sprites[runtime->player.sprites[length]->index]->resolution.height) / spriteHeight) / 256;
          int color = runtime->file.sprites[runtime->player.sprites[length]->index]->data[runtime->file.sprites[runtime->player.sprites[length]->index]->resolution.width * texY + texX]; //get current color from the texture
          if((color & 0x00FFFFFF) != 0) runtime->mlx.data[y * runtime->file.resolution.width + stripe] = color; //paint pixel if it isn't black, black is the invisible color
        }
      }
	  length++;
    }
}

int		update_image(t_runtime *runtime)
{
	static bool		editing;
	static clock_t	last_frame;
	t_ray			ray;

	if (runtime->player.updated || editing)
		return (1);
	if (last_frame && 1000000 / MAX_FPS > clock() - last_frame)
		return (2);
	editing = true;
	last_frame = clock();
	runtime->mlx.image = mlx_new_image(runtime->mlx.mlx, runtime->file.resolution.width, runtime->file.resolution.height);
	runtime->mlx.data = image_data(runtime->mlx.image, runtime->file.resolution.width);

	ray = (t_ray){{sin(runtime->player.degree * M_PI / 180), -1 * cos(runtime->player.degree * M_PI / 180)}, {cos(runtime->player.degree * M_PI / 180) * FOV / 100, sin(runtime->player.degree * M_PI / 180) * FOV / 100}};

	update_floor(runtime, ray);
	update_wall(runtime, ray);
	update_sprite(runtime, ray);

	mlx_put_image_to_window(runtime->mlx.mlx, runtime->mlx.window, runtime->mlx.image, 0, 0);
	runtime->player.updated = true;
	editing = false;
	update_keys(runtime);
	if (runtime->save)
	{
		bitmap("save.bmp", runtime);
		runtime->save = false;
	}
	mlx_destroy_image(runtime->mlx.mlx, runtime->mlx.image);
	if (runtime->end)
		end(runtime);
	return (0);
}