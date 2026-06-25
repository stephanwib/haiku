#include <stdio.h>
#include <sys/types.h>


#include <Directory.h>
#include <Entry.h>
#include <Path.h>
#include <VolumeRoster.h>
#include <Volume.h>
#include <fs_info.h>

int
main()
{
	BVolumeRoster roster;
	BVolume volume;

	printf("Listing volumes:\n");

	status_t status;
	while ((status = roster.GetNextVolume(&volume)) == B_OK) {
		char name[B_FILE_NAME_LENGTH];
		fs_info info;

		printf("--------------------------------------------------\n");

		status_t result = volume.GetName(name);
		if (result != B_OK) {
			fprintf(stderr, "GetName() failed: %" B_PRId32 "\n", result);
			snprintf(name, sizeof(name), "<unnamed>");
		}

		dev_t device = volume.Device();

		printf("[BVolume]\n");
		printf("Name: %s\n", name);
		printf("Device ID: %" B_PRIdDEV "\n", device);

		printf("Major: %u\n", (unsigned)major(device));
		printf("Minor: %u\n", (unsigned)minor(device));


		printf("Persistent: %s\n",
			volume.IsPersistent() ? "yes" : "no");
		printf("Removable: %s\n",
			volume.IsRemovable() ? "yes" : "no");
		printf("Read only: %s\n",
			volume.IsReadOnly() ? "yes" : "no");
		printf("Shared: %s\n",
			volume.IsShared() ? "yes" : "no");
		printf("Knows MIME: %s\n",
			volume.KnowsMime() ? "yes" : "no");
		printf("Knows Attr: %s\n",
			volume.KnowsAttr() ? "yes" : "no");
		printf("Knows Query: %s\n",
			volume.KnowsQuery() ? "yes" : "no");

		printf("\n[Root Directory]\n");

		BDirectory root;
		result = volume.GetRootDirectory(&root);

		if (result == B_OK) {
			printf("GetRootDirectory(): B_OK\n");

			BEntry entry;
			result = root.GetEntry(&entry);

			if (result == B_OK) {
				printf("GetEntry(): B_OK\n");

				BPath path;
				result = entry.GetPath(&path);

				if (result == B_OK)
					printf("Path: %s\n", path.Path());
				else
					printf("GetPath(): %" B_PRId32 "\n", result);
			} else {
				printf("GetEntry(): %" B_PRId32 "\n", result);
			}
		} else {
			printf("GetRootDirectory(): %" B_PRId32 "\n", result);
		}

		printf("\n[fs_stat_dev]\n");

		result = fs_stat_dev(device, &info);

		if (result == B_OK) {
			printf("Filesystem: %s\n", info.fsh_name);
			printf("Flags: 0x%08" B_PRIx32 "\n", info.flags);
			printf("Block size: %" B_PRIdOFF "\n", info.block_size);
			printf("Total blocks: %" B_PRIdOFF "\n", info.total_blocks);
			printf("Free blocks: %" B_PRIdOFF "\n", info.free_blocks);
		} else {
			printf("fs_stat_dev(): %" B_PRId32 "\n", result);
		}

		printf("\n");
	}

	if (status != B_ENTRY_NOT_FOUND) {
		fprintf(stderr,
			"GetNextVolume() terminated with error: %" B_PRId32 "\n",
			status);
	}



printf("\n==================================================\n");
printf("Testing next_dev()\n");
printf("==================================================\n");

int32 cookie = 0;
dev_t device;

while ((device = next_dev(&cookie)) >= 0) {
    printf("Device ID: %" B_PRIdDEV "\n", device);


    printf("Major: %u\n", (unsigned)major(device));
    printf("Minor: %u\n", (unsigned)minor(device));

    printf("Device ID (hex): 0x%llx\n",
        (unsigned long long)device);

    fs_info info;
    status_t result = fs_stat_dev(device, &info);

    if (result == B_OK) {
        printf("[fs_stat_dev]\n");
        printf("Filesystem: %s\n", info.fsh_name);
        printf("Flags: 0x%08" B_PRIx32 "\n", info.flags);
        printf("Block size: %" B_PRIdOFF "\n", info.block_size);
        printf("Total blocks: %" B_PRIdOFF "\n", info.total_blocks);
        printf("Free blocks: %" B_PRIdOFF "\n", info.free_blocks);
    } else {
        printf("fs_stat_dev() error: %" B_PRId32 "\n", result);
		return 0;
    }

    printf("--------------------------------------------------\n");
}

	return 0;
}
