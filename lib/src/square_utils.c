/*
** EPITECH PROJECT, 2025
** File description:
** square_utils
*/

#include <unistd.h>
#include <stdlib.h>

void find_largest_square(int *dp, int width, int height, int *max_size, int *max_i, int *max_j)
{
    *max_size = 0;
    *max_i = 0;
    *max_j = 0;
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            if (dp[j * width + i] > *max_size) {
                *max_size = dp[j * width + i];
                *max_i = i;
                *max_j = j;
            }
        }
    }
}

void mark_largest_square(char *map, int width, int height, int max_size, int max_i, int max_j)
{
    char *grid_start = map;
    while (*grid_start && *grid_start != '\n')
        grid_start++;
    if (*grid_start == '\n')
        grid_start++;
    
    int start_i = max_i - max_size + 1;
    int start_j = max_j - max_size + 1;

    for (int j = start_j; j <= max_j; j++) {
        for (int i = start_i; i <= max_i; i++) {
            int index = j * (width + 1) + i;
            if (grid_start[index] == '.')
                grid_start[index] = 'x';
        }
    }
}

void print_final_map(char *map, int width, int height)
{
    char *grid_start = map;
    while (*grid_start && *grid_start != '\n')
        grid_start++;
    if (*grid_start == '\n')
        grid_start++;
    
    size_t grid_length = height * (width + 1);
    ssize_t written_bytes __attribute__((unused)) = write(1, grid_start, grid_length);
}