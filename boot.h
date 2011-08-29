#pragma once
#include <stdint.h>

#define FAT_OEM_NAME_LENGTH 8
#define FAT_LABEL_LENGTH 11
#define FAT_FS_TYPE_LENGTH 8
#define FAT_OS_BOOT_CODE_LENGTH 448

#pragma pack(push)
#pragma pack(1)

struct fat_preamble {
  unsigned char jump_instruction[3];
  char oem_name[FAT_OEM_NAME_LENGTH]; /* e.g. "mkdosfs\0" or "BSD  4.4" */
};

struct fat_bios_parameter_block {
  uint16_t bytes_per_sector; /* commonly 512 */
  uint8_t sectors_per_cluster; /* powers of 2, 1 ~ 128 */
  uint16_t reserved_sector_count; /* sectors before first FAT */
  uint8_t fat_count; /* almost always 2, sometimes 1, rarely more. */
  uint16_t max_root_entries;
  uint16_t total_sectors; /* if 0, check total_sectors_large */
  unsigned char media_descriptor; /* 0xF8 is fixed disk. First byte of each FAT should match this. */
  uint16_t sectors_per_fat;
  uint16_t sectors_per_track; /* for disks with geometry */
  uint16_t head_count; /* for disks with geometry, e.g. 2 for double-sided floppy. */
  uint32_t sectors_before_partition; /* zero for non-partitined disk. */
  uint32_t total_sectors_large; /* only used if total_sectors == 0, value > 65535 */
};

struct fat16_extended_bios_parameter_block {
  unsigned char physical_drive_number; /* 0x00 = removable, 0x80 = hard disk */
  unsigned char current_head; /* reserved, Windows NT uses bits one and two as flags. */
  unsigned char extended_boot_signature; /* 0x29 indicates the following three entries exist. */
  uint32_t serial_number;
  char label[FAT_LABEL_LENGTH]; /* volume label, padded with spaces (0x20) */
  char fs_type[FAT_FS_TYPE_LENGTH]; /* padded with spaces (0x20) e.g "FAT16   " */
  unsigned char os_boot_code[FAT_OS_BOOT_CODE_LENGTH];
  unsigned char boot_sector_signature; /* hex 55AA */
};

struct fat16_boot_sector {
  struct fat_preamble preamble;
  struct fat_bios_parameter_block bios_params;
  struct fat16_extended_bios_parameter_block ext_bios_params;
};

#pragma pack(pop)

