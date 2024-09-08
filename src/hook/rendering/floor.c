#include "cub3D.h"
#include "rendering.h"

void draw_floor(mlx_image_t *image, float plane[2]) {
  float ray[4] = {
      data.player.direction[0] - plane[0],
      data.player.direction[1] - plane[1],
      data.player.direction[0] + plane[0],
      data.player.direction[1] + plane[1],
  };

  float middle = image->height / 2;
  for (unsigned short y = 0; y < middle; y++) {
    float distance = middle / (y - middle);

    double current[2] = {
        distance * ray[0] - data.player.position[0],
        distance * ray[1] - data.player.position[1],
    };

    float step[2] = {
        distance * (ray[2] - ray[0]) / image->width,
        distance * (ray[3] - ray[1]) / image->width,
    };

    draw((mlx_image_t *[2]){image, data.texture[CEIL]},
         (int[4]){0, y, image->width, y},
         (float[]){-current[0] * data.texture[CEIL]->width,
                   current[1] * data.texture[CEIL]->height},
         (float[]){-step[0] * data.texture[CEIL]->width,
                   step[1] * data.texture[CEIL]->height});

    unsigned short reverse_y = image->height - y - 1;
    draw((mlx_image_t *[2]){image, data.texture[FLOOR]},
         (int[4]){0, reverse_y, image->width, reverse_y},
         (float[]){-current[0] * data.texture[FLOOR]->width,
                   -current[1] * data.texture[FLOOR]->height},
         (float[]){-step[0] * data.texture[FLOOR]->width,
                   -step[1] * data.texture[FLOOR]->height});
  }
}
