#include "hook.h"
#include "cub3D.h"

void hook_key(mlx_key_data_t keydata, void *param) {
  if (keydata.key == MLX_KEY_ESCAPE)
    mlx_close_window(data.mlx);
}

void hook_generic(void *param) {
  unsigned short fps = (unsigned short)(1 / data.mlx->delta_time);
  float movement = MOVEMENT / fps;
  float rotation = MOVEMENT / fps / 2;

  if (mlx_is_key_down(data.mlx, MLX_KEY_W))
    move((float[2]){movement, 0});
  if (mlx_is_key_down(data.mlx, MLX_KEY_S))
    move((float[2]){-movement, 0});
  if (mlx_is_key_down(data.mlx, MLX_KEY_A))
    move((float[2]){0, movement});
  if (mlx_is_key_down(data.mlx, MLX_KEY_D))
    move((float[2]){0, -movement});

  if (mlx_is_key_down(data.mlx, MLX_KEY_LEFT))
    rotate(-rotation);
  if (mlx_is_key_down(data.mlx, MLX_KEY_RIGHT))
    rotate(rotation);
}

void hook_loop(void *param) {
  static mlx_image_t *image = NULL;
  if (image != NULL)
    mlx_delete_image(data.mlx, image);
  image = mlx_new_image(data.mlx, WIDTH, HEIGHT);
  mlx_image_to_window(data.mlx, image, 0, 0);
  mlx_set_instance_depth(image->instances, 0);

  float fov = (float)data.mlx->width / (float)data.mlx->height / 2.0f;
  float plane[2] = {-fov * data.player.direction[1],
                    fov * data.player.direction[0]};
  double distance_wall[image->width];

  draw_floor(image, plane);
  draw_wall(image, plane, distance_wall);
  draw_sprite(data.mlx, fov, distance_wall);
}
