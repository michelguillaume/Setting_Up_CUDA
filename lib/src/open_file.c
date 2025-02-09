/*
** EPITECH PROJECT, 2025
** File description:
** open_file
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

char *open_file(const char *file_path)
{
    int fd = open(file_path, O_RDONLY);
    if (fd == -1)
        return (NULL);

    int size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    if (!size || size == -1) {
        close(fd);
        return (NULL);
    }

    char *buffer = malloc(sizeof(char) * (size + 1));
    if (!buffer) {
        close(fd);
        return (NULL);
    }

    if (read(fd, buffer, size) == -1) {
        close(fd);
        free(buffer);
        return (NULL);
    }
    buffer[size] = '\0';
    close(fd);
    return (buffer);
}
