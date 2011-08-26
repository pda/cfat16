#include <stdint.h>

// 36 byte boot sector

#pragma pack(push)
#pragma pack(1)
struct fat16_boot_sector {
  unsigned char jump_instruction[3];
  char oem_name[8]; // "mkdosfs\0"
  uint16_t bytes_per_sector; // commonly 512
  uint8_t sectors_per_cluster; // powers of 2, 1 ~ 128
  uint16_t reserved_sector_count; // sectors before first FAT
  uint8_t fat_count; // almost always 2, sometimes 1, rarely more.
  uint16_t max_root_entries;
  uint16_t total_sectors; // if 0, check total_sectors_large
  unsigned char media_descriptor; // 0xF8 is fixed disk. First byte of each FAT should match this.
  uint16_t sectors_per_fat;
  uint16_t sectors_per_track; // for disks with geometry
  uint16_t head_count; // for disks with geometry, e.g. 2 for double-sided floppy.
  uint32_t sectors_before_partition; // zero for non-partitined disk.
  uint32_t total_sectors_large; // only used if total_sectors == 0, value > 65535
};
#pragma pack(pop)

void print_boot_sector();
