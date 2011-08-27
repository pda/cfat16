#include <stdio.h>

#include "boot.h"

struct fat16_filesystem {
  FILE * fd;
  struct fat16_boot_sector boot_sector;
};

void fat_open_filesystem(struct fat16_filesystem *, char * path);
void fat_close_filesystem(struct fat16_filesystem *);
