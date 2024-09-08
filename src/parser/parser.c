#include "parser.h"
#include "cub3D.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>

void parse(char *path) {
  int fd = open(path, O_RDONLY);
  char *line = NULL;
  bool is_header = true;

  if (fd == -1)
    error(2, "Failed to open file %s\n", path);

  while ((line = get_next_line(fd)) != NULL) {
    if (!is_header)
      map(line);
    else if (line[0] == '\0')
      is_header = false;
    else
      header(line);
    free(line);
  }
}
