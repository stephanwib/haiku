#include <Directory.h>
#include <Entry.h>
#include <Path.h>
#include <stdio.h>

void
ListDirectory(const char* label, BDirectory& dir)
{
    printf("\nListing with %s:\n", label);

    dir.Rewind();

    BEntry entry;
    while (dir.GetNextEntry(&entry) == B_OK) {
        char name[B_FILE_NAME_LENGTH];
        entry.GetName(name);
        printf("  %s\n", name);
    }
}

int
main(int argc, char** argv)
{
    if (argc != 2) {
        printf("Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    const char* path = argv[1];


    BDirectory dir1(path);
    if (dir1.InitCheck() != B_OK) {
        printf("Failed to open directory from path\n");
        return 1;
    }

    printf("dir1 successfully opened\n");

    BDirectory dir2(dir1);
    if (dir2.InitCheck() != B_OK) {
        printf("Failed to create second BDirectory, status: %d\n", dir2.InitCheck());
        return 1;
    }

    printf("dir2 successfully created from dir1\n");

    ListDirectory("dir1", dir1);
    ListDirectory("dir2", dir2);

    return 0;
}
