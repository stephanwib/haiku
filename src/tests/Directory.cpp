#include <Entry.h>
#include <Directory.h>
#include <Path.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    if (argc != 2) {
        printf("Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    const char* path = argv[1];

    BEntry entry(path);
    if (entry.InitCheck() != B_OK) {
        printf("Failed to create BEntry\n");
        return 1;
    }

    BDirectory dir1(&entry);
    if (dir1.InitCheck() != B_OK) {
        printf("Failed to create first BDirectory\n");
        return 1;
    }

    BDirectory dir2(&dir1);
    if (dir2.InitCheck() != B_OK) {
        printf("Failed to create second BDirectory\n");
        return 1;
    }

    BPath resolvedPath;
    entry.GetPath(&resolvedPath);
    printf("Listing directory: %s\n\n", resolvedPath.Path());

    BEntry child;
    while (dir2.GetNextEntry(&child) == B_OK) {
        BPath childPath;
        child.GetPath(&childPath);
        printf("%s\n", childPath.Leaf());
    }

    return 0;
}
