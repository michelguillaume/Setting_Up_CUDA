/*
** EPITECH PROJECT, 2025
** File description:
** map_parser
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

static bool is_valid_number(const char *str)
{
    if (!str || *str == '\0')
        return false;

    for (int i = 0; str[i] != '\n' && str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

static int get_map_height(const char *map)
{
    if (!is_valid_number(map)) {
        fprintf(stderr, "Error: The first line must contain a valid positive integer for height.\n");
        return -1;
    }
    return atoi(map);
}

int get_map_width(const char *ptr)
{
    int width = 0;
    while (ptr[width] && ptr[width] != '\n')
        width++;
    return width;
}

static bool validate_map_format(const char *ptr, int width, int height)
{
    int line_count = 0;

    while (*ptr) {
        int line_length = 0;

        while (ptr[line_length] && ptr[line_length] != '\n') {
            if (ptr[line_length] != '.' && ptr[line_length] != 'o') {
                fprintf(stderr, "Error: Invalid character '%c' in line %d.\n",
                        ptr[line_length], line_count + 1);
                return false;
            }
            line_length++;
        }

        if (line_length != width) {
            fprintf(stderr, "Error: Line %d has incorrect width (%d instead of %d).\n",
                    line_count + 1, line_length, width);
            return false;
        }

        if (ptr[line_length] != '\n') {
            fprintf(stderr, "Error: Line %d does not end with '\\n'.\n", line_count + 1);
            return false;
        }

        line_count++;
        ptr += line_length + 1;
    }

    if (line_count != height) {
        fprintf(stderr, "Error: Incorrect number of lines (%d instead of %d).\n",
                line_count, height);
        return false;
    }

    return true;
}

bool get_map_dimensions(const char *map, int *width, int *height)
{
    *height = get_map_height(map);
    if (*height <= 0)
        return false;

    const char *ptr = map;
    while (*ptr && *ptr != '\n') ptr++;
    if (!*ptr) {
        fprintf(stderr, "Error: Malformed file, no map data after height.\n");
        return false;
    }
    ptr++;

    *width = get_map_width(ptr);
    if (*width == 0) {
        fprintf(stderr, "Error: Invalid width value.\n");
        return false;
    }

    return validate_map_format(ptr, *width, *height);
}

int *convert_map_to_grid(const char *map, int width, int height)
{
    int *grid = (int*)malloc(width * height * sizeof(int));

    if (!grid) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return NULL;
    }

    const char *ptr = map;

    while (*ptr && *ptr != '\n') ptr++;
    ptr++;
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++, ptr++) {
            grid[y * width + x] = (*ptr == '.') ? 1 : 0;
        }
        ptr++;
    }
    return grid;
}
