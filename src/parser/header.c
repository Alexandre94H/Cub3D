#include "cub3D.h"
#include <stdio.h>
#include <string.h>

static mlx_image_t *load(char *value) {
  mlx_image_t *image;
  short rgb[3];

  if (sscanf(value, "%hd, %hd, %hd", &rgb[0], &rgb[1], &rgb[2]) == 3) {
    int color = (rgb[0] << 24) | (rgb[1] << 16) | (rgb[2] << 8) | 0xff;
    image = mlx_new_image(data.mlx, 1, 1);
    mlx_put_pixel(image, 0, 0, color);
  } else {
    xpm_t *xpm = mlx_load_xpm42(value);
    if (xpm == NULL)
      error(3, "Failed to load xpm %s: %s\n", value, mlx_strerror(mlx_errno));
    image = mlx_texture_to_image(data.mlx, &xpm->texture);
    mlx_delete_xpm42(xpm);
  }

  return image;
}

void header(char *line) {
  char *comp = "NESWFC";
  texture_t type = strchr(comp, line[0]) - comp;
  if (type == SOUTH && line[1] == ' ')
    type = SPRITE;
  data.texture[type] = load(strchr(line, ' ') + 1);
}
