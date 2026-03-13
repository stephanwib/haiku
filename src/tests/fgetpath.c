#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <limits.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *path = argv[1];

    DIR *dir = opendir(path);
    if (!dir) {
        perror("opendir");
        return EXIT_FAILURE;
    }

    int fd = dirfd(dir);
    if (fd == -1) {
        perror("dirfd");
        closedir(dir);
        return EXIT_FAILURE;
    }

    char resolved_path[PATH_MAX];
  
    if (fcntl(fd, F_GETPATH, resolved_path) == -1) {
        perror("fcntl(F_GETPATH)");
        closedir(dir);
        return EXIT_FAILURE;
    }

    printf("Resolved path: %s\n", resolved_path);

    closedir(dir);
    return EXIT_SUCCESS;
}
