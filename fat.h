// 36 byte boot sector
struct fat16_boot_sector {
	char jump_instruction[3];
	char oem_name[8]; // "mkdosfs\0"
	char bytes_per_sector[2]; // commonly 512
	char sectors_per_cluster; // powers of 2, 1 ~ 128
	char reserved_sector_count[2]; // sectors before first FAT
	char fat_count[2]; // almost always 2, sometimes 1, rarely more.
	char max_root_entries[2];
	char total_sectors[2]; // if 0, check total_sectors_large
	char media_descriptor; // 0xF8 is fixed disk. First byte of each FAT should match this.
	char sectors_per_fat[2];
	char sectors_per_track[2]; // for disks with geometry
	char head_count[2]; // for disks with geometry, e.g. 2 for double-sided floppy.
	char sectors_before_partition[4]; // zero for non-partitined disk.
	char total_sectors_large[4]; // only used if total_sectors == 0, value > 65535
};
