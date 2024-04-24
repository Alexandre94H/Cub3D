#include "functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

t_data g_data = {0};

void error(int code, char *str, ...) {
	va_list args;

	va_start(args, str);
	vfprintf(stderr, str, args);
	va_end(args);
	exit(code);
}

int main(int argc, char **argv) {
	if (argc != 2)
		error(1, "Usage: %s <file>\n", argv[0]);
	load_file(argv[1]);

	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_t *mlx = mlx_init(g_data.resolution[0], g_data.resolution[1], argv[0], true);

	mlx_key_hook(mlx, key, mlx);
	mlx_resize_hook(mlx, resize, mlx);
	mlx_loop_hook(mlx, hook_generic, mlx);
	mlx_loop_hook(mlx, loop, mlx);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	free(g_data.map.data);
}
