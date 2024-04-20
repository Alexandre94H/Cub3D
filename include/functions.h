#pragma once

#include "types.h"

// main.c
void error(int code, char *str, ...);

// file.c
t_file load_file(char *filename);

// loop.c
void loop(void* param);

// hook.c
void key(mlx_key_data_t keydata, void* param);
