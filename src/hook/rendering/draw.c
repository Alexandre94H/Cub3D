#include "cub3D.h"
#include <math.h>

unsigned int image_color(mlx_image_t *image, unsigned short index[2]) {
    if (index[0] >= image->width || index[1] >= image->height) return 0;

    unsigned char *ptr = image->pixels + (index[1] * image->width + index[0]) * 4;
    return ptr[0] << 24 | ptr[1] << 16 | ptr[2] << 8 | ptr[3];
}

void draw(mlx_image_t *image[2], int pixel[4], float start[2], float step[2]) {
    double current[2] = {start[0], start[1]};
    for (int x = pixel[0]; x <= pixel[2]; x++)
        for (int y = pixel[1]; y <= pixel[3]; y++) {
            double texture_x = floor(current[0]);
            double texture_y = floor(current[1]);
            texture_x -= floor(texture_x / image[1]->width) * image[1]->width;
            texture_y -= floor(texture_y / image[1]->height) * image[1]->height;
            current[0] += step[0];
            current[1] += step[1];

            if (x >= 0 && x < (int) image[0]->width && y >= 0 && y < (int) image[0]->height)
                mlx_put_pixel(image[0], x, y, image_color(image[1], (unsigned short[]) {texture_x, texture_y}));
        }
}
