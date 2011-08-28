#include "filesystem.h"
#include "dir.h"
#include "utils.h"

void fat_open_filesystem(struct fat16_filesystem * fs, char * path) {
  struct fat_bios_parameter_block * bp;

  if (!(fs->fd = fopen(path, "r"))) {
    fatal_error("unable to fopen filesystem");
  }

  if (!fread(&fs->boot_sector, sizeof(fs->boot_sector), 1, fs->fd)) {
    fatal_error("unable to read boot sector");
  }

  /* calculate and store commonly used parameters */
  bp = &fs->boot_sector.bios_params;
  fs->fat_offset = bp->bytes_per_sector * bp->reserved_sector_count;
  fs->fat_size = bp->bytes_per_sector * bp->sectors_per_fat;
  fs->root_dir_offset = fs->fat_offset + (fs->fat_size * bp->fat_count);
  fs->root_dir_size = bp->max_root_entries * sizeof(struct fat16_directory_entry);
  fs->root_dir_entries = bp->max_root_entries;
  fs->data_offset = fs->root_dir_offset + fs->root_dir_size;
}

void fat_close_filesystem(struct fat16_filesystem * fs) {
  if (fclose(fs->fd) != 0) fatal_error("unable to close filesystem");
}

int fat_seek_to_root_directory(struct fat16_filesystem * fs) {
  return fseek(fs->fd, fs->root_dir_offset, SEEK_SET);
}
