#pragma once
#include <stdint.h>

#define FAT_FILENAME_LENGTH 8
#define FAT_EXTENSION_LENGTH 3

#pragma pack(push)
#pragma pack(1)

struct fat_dir_entry {
  unsigned char name[FAT_FILENAME_LENGTH]; /* e.g. "README  " */
  unsigned char extension[FAT_EXTENSION_LENGTH]; /* e.g. "TXT" */
  unsigned char attributes; /* File Attributes bitfield: ro,hide,sys,label,subdir,arch,dev,unused */
  unsigned char nt_case; /* NT uses two bits to encode case information */
  uint8_t create_time_fine; /* 10ms units, 0 ~ 199 */
  uint16_t create_time; /* bitfield: 15~11: hours (0~23), 10~5: minutes (0~59), 4~0: seconds/2 (0-29) */
  uint16_t create_date; /* bitfield: 15~9: year (1980~2107), 8~5: month (1~12), 4~0: day (1~31) */
  uint16_t access_date; /* see create_date */
  uint16_t ea_index; /* used by OS/2 and NT, different meaning in FAT32 */
  uint16_t modify_time; /* see create_time */
  uint16_t modify_date; /* see create_date */
  uint16_t start_cluster; /* first cluster of data */
  uint32_t size; /* file size in bytes. */
};

#pragma pack(pop)

void fat_read_filename(char * output, struct fat_dir_entry *);
int fat_dir_entry_exists(struct fat_dir_entry *);
int fat_is_volume_label(struct fat_dir_entry *);
int fat_is_file(struct fat_dir_entry *);
int fat_is_dir(struct fat_dir_entry *);
