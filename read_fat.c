#include <stdlib.h>
#include <stdio.h>

#include "boot.h"
#include "time.h"
#include "dir.h"
#include "utils.h"

#define FS_PATH "sample.fat16"

/* header */
void print_root_directory();
void print_boot_sector();

/* implementation */
int main() {
  print_boot_sector();
  print_root_directory();
  putchar('\n');
  return EXIT_SUCCESS;
}

void print_root_directory() {
  FILE * fs;
  struct fat16_directory_entry entry;
  char filename[FAT_FILENAME_LENGTH + 1];
  char extension[FAT_EXTENSION_LENGTH + 1];
  struct fat_date date_created, date_modified, date_accessed;
  struct fat_time time_created, time_modified;
  int i;

  fs = fopen(FS_PATH, "r");
  /* TODO: delete FAT_ROOT_OFFSET, seek reserved_sector_count * bytes_per_sector */
  fseek(fs, FAT_ROOT_OFFSET, SEEK_SET);

  putchar('\n');
  printf("Root directory:\n");
  /* TODO: iterate max_root_entries times. */
  for (i = 0; i < 512; i++) {
    fread(&entry, sizeof(entry), 1, fs);

    /* skip empty entries */
    if (!*entry.name) continue;

    /* null terminate strings */
    fat_string_copy(filename, entry.name, FAT_FILENAME_LENGTH);
    fat_string_copy(extension, entry.extension, FAT_EXTENSION_LENGTH);

    /* read dates and times from bitfields */
    fat_read_date(&date_created, entry.create_date);
    fat_read_date(&date_modified, entry.modify_date);
    fat_read_date(&date_accessed, entry.access_date);
    fat_read_time(&time_created, entry.create_time);
    fat_read_time(&time_modified, entry.modify_time);

    if (entry.attributes & 0x08) {
      printf("  (Volume label: %s%s)\n", filename, extension);
    } else {
      printf("  %s.%s\n", filename, extension);
    }

    printf("    bytes: %d\n", entry.size);
    printf("    cluster: %d\n", entry.start_cluster);
    printf("    created: %4u-%02u-%02u %02u:%02u:%02u\n",
        date_created.year, date_created.month, date_created.day,
        time_created.hour, time_created.minute, time_created.second);
    printf("   ");
    printf(" ro:%s", entry.attributes & 0x01 ? "yes" : "no");
    printf(" hide:%s", entry.attributes & 0x02 ? "yes" : "no");
    printf(" sys:%s", entry.attributes & 0x03 ? "yes" : "no");
    printf(" dir:%s", entry.attributes & 0x10 ? "yes" : "no");
    printf(" arch:%s", entry.attributes & 0x20 ? "yes" : "no");
    putchar('\n');
  }

  fclose(fs);
}

void print_boot_sector() {
  FILE * fs;
  struct fat16_boot_sector bs;
  struct fat_preamble * pre;
  struct fat_bios_parameter_block * bp;
  struct fat16_extended_bios_parameter_block * ebp;

  /* presentation variables */
  int total_sectors;
  char oem_name[FAT_OEM_NAME_LENGTH + 1];
  char label[FAT_LABEL_LENGTH + 1];
  char fs_type[FAT_FS_TYPE_LENGTH + 1];

  fs = fopen(FS_PATH, "r");
  fread(&bs, sizeof(bs), 1, fs);
  fclose(fs);

  pre = &bs.preamble;
  bp = &bs.bios_params;
  ebp = &bs.ext_bios_params;

  total_sectors = bp->total_sectors == 0 ? (int)bp->total_sectors_large : (int)bp->total_sectors;

  /* null terminate strings */
  fat_string_copy(oem_name, pre->oem_name, FAT_OEM_NAME_LENGTH);
  fat_string_copy(label, ebp->label, FAT_LABEL_LENGTH);
  fat_string_copy(fs_type, ebp->fs_type, FAT_FS_TYPE_LENGTH);

  putchar('\n');
  printf("Boot sector size: %d bytes\n", (int)sizeof(bs));
  printf("Jump instruction: %X %X %X\n", pre->jump_instruction[0], pre->jump_instruction[1], pre->jump_instruction[2]);
  printf("OEM name: %s\n", oem_name);

  printf("\nBIOS parameters:\n");
  printf("  Bytes per sector: %d\n", bp->bytes_per_sector);
  printf("  Sectors per cluster: %d\n", bp->sectors_per_cluster);
  printf("  Reserved sectors: %d\n", bp->reserved_sector_count);
  printf("  Number of FATs: %d\n", bp->fat_count);
  printf("  Maximum root entries: %d\n", bp->max_root_entries);
  printf("  Total sectors: %d (small: %d, large: %d)\n", total_sectors, bp->total_sectors, bp->total_sectors_large);
  printf("  Media descriptor: 0x%02X%s\n", bp->media_descriptor, bp->media_descriptor == 0xf8 ? " (fixed disk)" : "");
  printf("  Sectors per FAT: %d\n", bp->sectors_per_fat);
  printf("  Sectors per track: %d\n", bp->sectors_per_track);
  printf("  Number of heads: %d\n", bp->head_count);
  printf("  Sectors before partition: %d\n", bp->sectors_before_partition);

  printf("\nExtended BIOS parameters:\n");
  printf("  Physical drive code: 0x%02X (%s)\n", ebp->physical_drive_number, ebp->physical_drive_number ? "physical" : "removable");
  printf("  Reserved byte (WinNT): 0x%02X\n", ebp->current_head);
  printf("  Extended boot signature: 0x%02X\n", ebp->extended_boot_signature);
  printf("  Volume serial number: 0x%08X\n", ebp->serial_number);
  printf("  Volume label: %11s\n", label);
  printf("  FAT type: %s\n", fs_type);
  printf("  OS boot code: %d bytes\n", (int)sizeof(ebp->os_boot_code));
  printf("  Boot sector signature: 0x%04X\n", ebp->boot_sector_signature);
}
