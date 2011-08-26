#include <stdlib.h>
#include <stdio.h>

#include "fat.h"

#define FS_PATH "sample.fat16"

int main() {
  print_boot_sector();
  return EXIT_SUCCESS;
}

void print_boot_sector() {
  FILE * fs;
  struct fat16_boot_sector bs;

  fs = fopen(FS_PATH, "r");
  fread(&bs, sizeof(bs), 1, fs);
  fclose(fs);

  putchar('\n');
  printf("Boot sector size: %d bytes\n", (int)sizeof(bs));
  printf("Jump instruction: %X %X %X\n", bs.jump_instruction[0], bs.jump_instruction[1], bs.jump_instruction[2]);
  printf("OEM name: %s\n", bs.oem_name);
  printf("Bytes per sector: %d\n", bs.bytes_per_sector);
  printf("Sectors per cluster: %d\n", bs.sectors_per_cluster);
  printf("Reserved sectors: %d\n", bs.reserved_sector_count);
  printf("Number of FATs: %d\n", bs.fat_count);
  printf("Maximum root entries: %d\n", bs.max_root_entries);
  printf("Total sectors: %d", bs.total_sectors == 0 ? bs.total_sectors_large : bs.total_sectors);
  printf(" (small: %d, large: %d)\n", bs.total_sectors, bs.total_sectors_large);
  printf("Media descriptor: %X", bs.media_descriptor);
  printf(" (fixed disk? %s)\n", bs.media_descriptor == 0xf8 ? "yes" : "no");
  printf("Sectors per FAT: %d\n", bs.sectors_per_fat);
  printf("Sectors per track: %d\n", bs.sectors_per_track);
  printf("Number of heads: %d\n", bs.head_count);
  printf("Sectors before partition: %d\n", bs.sectors_before_partition);
  putchar('\n');
}
