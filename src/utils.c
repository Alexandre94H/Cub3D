#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void error(int code, char *format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    exit(code);
}
