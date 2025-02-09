#ifndef SQUARE_UTILS_H
#define SQUARE_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

void find_largest_square(int *dp, int width, int height, int *max_size, int *max_i, int *max_j);

void mark_largest_square(char *map, int width, int height, int max_size, int max_i, int max_j);

void print_final_map(char *map, int width, int height);

#ifdef __cplusplus
}
#endif

#endif
