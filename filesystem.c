#include "filesystem.h"
#include "utils.h"

void fat_open_filesystem(struct fat16_filesystem * fs, char * path) {
  if (!(fs->fd = fopen(path, "r"))) {
    fatal_error("unable to fopen filesystem");
  }

  if (!fread(&fs->boot_sector, sizeof(fs->boot_sector), 1, fs->fd)) {
    fatal_error("unable to read boot sector");
  }
}

void fat_close_filesystem(struct fat16_filesystem * fs) {
  if (fclose(fs->fd) != 0) fatal_error("unable to close filesystem");
}
