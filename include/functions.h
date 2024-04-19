#pragma once

#include "types.h"

// main.c
void error(int code, char *str, ...);

// file.c
t_file load_file(char *filename);
