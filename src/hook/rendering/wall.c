#include "cub3D.h"
#include "rendering.h"
#include <math.h>

double dda(float ray[2], double side[2]) {
  unsigned short current[2] = {
      floor(data.player.position[0]),
      floor(data.player.position[1]),
  };

  float delta[2] = {
      fabs(1 / ray[0]),
      fabs(1 / ray[1]),
  };

  side[0] = ray[0] < 0 ? (data.player.position[0] - current[0]) * delta[0]
                       : (current[0] + 1 - data.player.position[0]) * delta[0];
  side[1] = ray[1] < 0 ? (data.player.position[1] - current[1]) * delta[1]
                       : (current[1] + 1 - data.player.position[1]) * delta[1];

  while (true) {
    if (side[0] < side[1])
      current[0] += ray[0] < 0 ? -1 : 1;
    else
      current[1] += ray[1] < 0 ? -1 : 1;

    if (data.map.data[current[1] * data.map.size[0] + current[0]] != 0)
      break;

    if (side[0] < side[1])
      side[0] += delta[0];
    else
      side[1] += delta[1];
  };

  return side[0] < side[1] ? side[0] : side[1];
}

void draw_wall(mlx_image_t *image, float plane[2], double distance[]) {
  for (unsigned short x = 0; x < image->width; x++) {
    float norm_x = 2 * x / (float)image->width - 1;
    float ray[2] = {
        data.player.direction[0] + plane[0] * norm_x,
        data.player.direction[1] + plane[1] * norm_x,
    };

    double side[2];
    distance[x] = dda(ray, side);

    int height = image->height / distance[x];
    int line[2] = {
        -height / 2 + image->height / 2,
        height / 2 + image->height / 2,
    };

    mlx_image_t *texture =
        side[0] < side[1] ? ray[0] < 0 ? data.texture[WEST] : data.texture[EAST]
        : ray[1] < 0 ? data.texture[NORTH]
                          : data.texture[SOUTH];

    double wall_x = side[0] < side[1]
                        ? data.player.position[1] + side[0] * ray[1]
                        : data.player.position[0] + side[1] * ray[0];
    wall_x -= floor(wall_x);

    unsigned short texture_x = wall_x * texture->width;
    if ((side[0] < side[1] && ray[0] < 0) || (side[0] > side[1] && ray[1] > 0))
      texture_x = texture->width - texture_x - 1;

    draw((mlx_image_t *[2]){image, texture},
         (int[4]){x, line[0], x, line[1] - 1}, (float[]){texture_x, 0},
         (float[]){0, (float)texture->height / height});
  }
}
