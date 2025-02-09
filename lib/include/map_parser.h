#ifndef MAP_PARSER_H
#define MAP_PARSER_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

bool get_map_dimensions(const char *map, int *width, int *height);

int *convert_map_to_grid(const char *map, int width, int height);

#ifdef __cplusplus
}
#endif

#endif
