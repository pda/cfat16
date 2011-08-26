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
  struct fat_preamble * pre;
  struct fat_bios_parameter_block * bp;

  fs = fopen(FS_PATH, "r");
  fread(&bs, sizeof(bs), 1, fs);
  fclose(fs);

  pre = &bs.preamble;
  bp = &bs.bios_params;

  putchar('\n');
  printf("Boot sector size: %d bytes\n", (int)sizeof(bs));
  printf("Jump instruction: %X %X %X\n", pre->jump_instruction[0], pre->jump_instruction[1], pre->jump_instruction[2]);
  printf("OEM name: %s\n", pre->oem_name);

  printf("\nBIOS parameters:\n");
  printf("  Bytes per sector: %d\n", bp->bytes_per_sector);
  printf("  Sectors per cluster: %d\n", bp->sectors_per_cluster);
  printf("  Reserved sectors: %d\n", bp->reserved_sector_count);
  printf("  Number of FATs: %d\n", bp->fat_count);
  printf("  Maximum root entries: %d\n", bp->max_root_entries);
  printf("  Total sectors: %d", bp->total_sectors == 0 ? bp->total_sectors_large : bp->total_sectors);
  printf("   (small: %d, large: %d)\n", bp->total_sectors, bp->total_sectors_large);
  printf("  Media descriptor: 0x%02X", bp->media_descriptor);
  printf("   (fixed disk? %s)\n", bp->media_descriptor == 0xf8 ? "yes" : "no");
  printf("  Sectors per FAT: %d\n", bp->sectors_per_fat);
  printf("  Sectors per track: %d\n", bp->sectors_per_track);
  printf("  Number of heads: %d\n", bp->head_count);
  printf("  Sectors before partition: %d\n", bp->sectors_before_partition);
}
