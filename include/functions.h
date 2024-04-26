#pragma once

#include "types.h"

// main.c
void error(int code, char *str, ...);

// file.c
void load_file(char *path);

// loop.c
void loop(void* param);

// hook.c
void hook_generic(void* param);
void key(mlx_key_data_t keydata, void* param);
void resize(int32_t width, int32_t height, void* param);
