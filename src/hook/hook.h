#ifndef HOOK_H
# define HOOK_H

# include "MLX42/MLX42.h"

//= Draw Functions =//

void draw_floor(mlx_image_t *image, float plane[2]);

void draw_wall(mlx_image_t *image, float plane[2], double distance[]);

void draw_sprite(mlx_t *mlx, float fov, double distance_wall[]);

//= Movement Functions =//

void move(const float movement[2]);

void rotate(float rotation);

//= Sorting Functions =//

void sort_sprite();

#endif
