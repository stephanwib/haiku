#include <stdio.h>

#include <VolumeRoster.h>
#include <Volume.h>
#include <fs_info.h>

int
main()
{
	BVolumeRoster roster;
	BVolume volume;

	printf("Listing volumes:\n");

	while (roster.GetNextVolume(&volume) == B_OK) {
		char name[B_FILE_NAME_LENGTH];
		fs_info info;

		if (volume.GetName(name) != B_OK)
			snprintf(name, sizeof(name), "<unnamed>");

		printf("--------------------------------------------------\n");
		printf("Name: %s\n", name);
		printf("Device ID: %" B_PRIdDEV "\n", volume.Device());

		if (fs_stat_dev(volume.Device(), &info) == B_OK) {
			printf("Filesystem: %s\n", info.fsh_name);
			printf("Flags: 0x%08" B_PRIx32 "\n", info.flags);
			printf("Block size: %" B_PRIdOFF "\n", info.block_size);
			printf("Total blocks: %" B_PRIdOFF "\n", info.total_blocks);
			printf("Free blocks: %" B_PRIdOFF "\n", info.free_blocks);
		}
	}

	return 0;
}
