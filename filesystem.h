#pragma once
#include <stdio.h>

#include "boot.h"
#include "dir.h"

struct fat16_filesystem {
  FILE * fd;
  struct fat16_boot_sector boot_sector;
  int fat_offset;
  int fat_size;
  int root_dir_offset;
  int root_dir_size;
  int root_dir_entries;
  int data_offset;
  int cluster_size;
};

void fat_open_filesystem(struct fat16_filesystem *, char * path);
void fat_close_filesystem(struct fat16_filesystem *);

int fat_seek_to_root_dir(struct fat16_filesystem *);
int fat_seek_to_cluster(struct fat16_filesystem *, int cluster);

char * fat_read_file_from_dir_entry(struct fat16_filesystem *, struct fat_dir_entry *);
