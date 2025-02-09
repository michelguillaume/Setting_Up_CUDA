/*
** EPITECH PROJECT, 2025
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cuda_runtime.h>

#include "open_file.h"
#include "map_parser.h"
#include "square_utils.h"

__device__ int min3(int a, int b, int c)
{
    int m = (a < b) ? a : b;
    return (m < c) ? m : c;
}

// Each thread processes one element of the anti-diagonal "diag".
// The grid (dp) is of size width x height and stored in linear memory.
__global__ void dp_kernel(int *dp, int width, int height, int diag)
{
    // Calculate the thread index within the anti-diagonal.
    int index = threadIdx.x + blockIdx.x * blockDim.x;

    // For the anti-diagonal with index "diag", the column indices vary from "start" to "end".
    int start = diag - (height - 1);
    if (start < 0)
        start = 0;
    int end = diag;
    if (end >= width)
        end = width - 1;
    int nbElem = end - start + 1;

    if (index < nbElem) {
        int i = start + index;   // Column index.
        int j = diag - i;        // Row index.

        // Only process cells with i > 0 and j > 0 (borders remain unchanged).
        if (i > 0 && j > 0 && i < width && j < height) {
            // If the cell is empty (represented by 1), update its value;
            // if it is an obstacle (represented by 0), do nothing.
            if (dp[j * width + i] != 0) {
                int top      = dp[(j - 1) * width + i];
                int left     = dp[j * width + (i - 1)];
                int top_left = dp[(j - 1) * width + (i - 1)];
                dp[j * width + i] = min3(top, left, top_left) + 1;
            }
        }
    }
}

// Process the anti-diagonals on the GPU.
void process_dp_on_gpu(int *d_grid, int width, int height)
{
    int threadsPerBlock = 256;
    // The total number of anti-diagonals is (width + height - 1).
    for (int diag = 1; diag < width + height - 1; diag++) {
        int start = diag - (height - 1);
        if (start < 0)
            start = 0;
        int end = diag;
        if (end >= width)
            end = width - 1;
        int nbElem = end - start + 1;
        int blocks = (nbElem + threadsPerBlock - 1) / threadsPerBlock;

        dp_kernel<<<blocks, threadsPerBlock>>>(d_grid, width, height, diag);
        cudaDeviceSynchronize(); // Ensure dependencies are respected.
    }
}

int main(int ac, const char* av[])
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

    // Allocate the grid on the GPU (the dp array).
    int *d_grid;
    size_t grid_size = width * height * sizeof(int);
    cudaError_t err = cudaMalloc((void**)&d_grid, grid_size);
    if (err != cudaSuccess) {
        fprintf(stderr, "cudaMalloc error: %s\n", cudaGetErrorString(err));
        free(grid);
        free(map);
        return 84;
    }
    cudaMemcpy(d_grid, grid, grid_size, cudaMemcpyHostToDevice);

    process_dp_on_gpu(d_grid, width, height);

    // Retrieve the computed dp matrix from the GPU.
    int *dp_host = (int *)malloc(grid_size);
    if (!dp_host) {
        fprintf(stderr, "Error: malloc failed.\n");
        cudaFree(d_grid);
        free(grid);
        free(map);
        return 84;
    }
    cudaMemcpy(dp_host, d_grid, grid_size, cudaMemcpyDeviceToHost);

    int max_size = 0, max_i = 0, max_j = 0;
    find_largest_square(dp_host, width, height, &max_size, &max_i, &max_j);
#ifdef DEBUG
    printf("Largest square size: %d at position (%d, %d)\n", max_size, max_i, max_j);
#endif


    mark_largest_square(map, width, height, max_size, max_i, max_j);

    print_final_map(map, width, height);

    free(dp_host);
    free(grid);
    cudaFree(d_grid);
    free(map);

    return 0;
}
