#include "functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

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

	g_data.file = load_file(argv[1]);

	g_data.player = (t_player){
		.pos = { g_data.file.player_pos[0] - 0.5, g_data.file.player_pos[1] + 0.5 },
		.dir = { sin(g_data.file.player_angle * M_PI / 180), -cos(g_data.file.player_angle * M_PI / 180) },
	};

	float ratio = (float)g_data.file.resolution[0] / g_data.file.resolution[1];
	g_data.player.plane[0] = -g_data.player.dir[1] / ratio;
	g_data.player.plane[1] = g_data.player.dir[0] / ratio;

	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_t *mlx = mlx_init(g_data.file.resolution[0], g_data.file.resolution[1], argv[0], true);
	mlx_key_hook(mlx, key, mlx);
	mlx_loop_hook(mlx, hook_generic, mlx);
	mlx_loop_hook(mlx, loop, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	free(g_data.file.map);
}
