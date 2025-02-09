/*
** EPITECH PROJECT, 2025
** File description:
** main_cpu
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "open_file.h"
#include "map_parser.h"
#include "square_utils.h"

// Compute the DP matrix on the CPU.
// dp is assumed to be a row-major array of size (height * width).
// For each cell (row, col) (with row and col starting at 0), if the cell is empty (nonzero),
// update dp[row*width + col] = min( dp[(row-1)*width + col],
//                                   dp[row*width + (col-1)],
//                                   dp[(row-1)*width + (col-1)] ) + 1;
// The first row and first column remain unchanged.
static void compute_dp_cpu(int *dp, int width, int height)
{
    for (int row = 1; row < height; row++) {
        for (int col = 1; col < width; col++) {
            if (dp[row * width + col] != 0) {
                int top = dp[(row - 1) * width + col];
                int left = dp[row * width + (col - 1)];
                int top_left = dp[(row - 1) * width + (col - 1)];
                int min_val = top;
                if (left < min_val)
                    min_val = left;
                if (top_left < min_val)
                    min_val = top_left;
                dp[row * width + col] = min_val + 1;
            }
        }
    }
}

int main(int ac, const char *av[])
{
    if (ac != 2)
        return 84;

    char *map = open_file(av[1]);
    if (!map)
        return 84;

    int width, height;
    if (!get_map_dimensions(map, &width, &height)) {
        free(map);
        return 84;
    }
#ifdef DEBUG
    printf("Map size: %d x %d\n", width, height);
#endif

    int *grid = convert_map_to_grid(map, width, height);
    if (!grid) {
        free(map);
        return 84;
    }

    compute_dp_cpu(grid, width, height);

    int max_size = 0, max_i = 0, max_j = 0;
    find_largest_square(grid, width, height, &max_size, &max_i, &max_j);
#ifdef DEBUG
    printf("Largest square size: %d at position (%d, %d)\n",
           max_size, max_i, max_j);
#endif

    mark_largest_square(map, width, height, max_size, max_i, max_j);
    print_final_map(map, width, height);

    free(grid);
    free(map);
    return 0;
}
