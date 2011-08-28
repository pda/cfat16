#include <stdio.h>

#include "boot.h"

struct fat16_filesystem {
  FILE * fd;
  struct fat16_boot_sector boot_sector;
  int fat_offset;
  int fat_size;
  int root_dir_offset;
  int root_dir_size;
  int root_dir_entries;
  int data_offset;
};

void fat_open_filesystem(struct fat16_filesystem *, char * path);
void fat_close_filesystem(struct fat16_filesystem *);

int fat_seek_to_root_directory(struct fat16_filesystem *);
