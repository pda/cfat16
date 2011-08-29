#include <stdlib.h>

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
  fs->root_dir_size = bp->max_root_entries * sizeof(struct fat_dir_entry);
  fs->root_dir_entries = bp->max_root_entries;
  fs->data_offset = fs->root_dir_offset + fs->root_dir_size;
  fs->cluster_size = bp->bytes_per_sector * bp->sectors_per_cluster;
}

void fat_close_filesystem(struct fat16_filesystem * fs) {
  if (fclose(fs->fd) != 0) fatal_error("unable to close filesystem");
}

int fat_seek_to_root_dir(struct fat16_filesystem * fs) {
  return fseek(fs->fd, fs->root_dir_offset, SEEK_SET);
}

int fat_seek_to_cluster(struct fat16_filesystem * fs, int cluster) {
  /* first cluster is #2 at position 0 */
  int offset = fs->data_offset + (cluster - 2) * fs->cluster_size;
  return fseek(fs->fd, offset, SEEK_SET);
}

char * fat_read_file_from_dir_entry(struct fat16_filesystem * fs, struct fat_dir_entry * de) {
  char * buffer;

  if (de->size > fs->cluster_size)
    fatal_error("TODO: read multi-cluster files");

  buffer = (char *)malloc(de->size + 1);
  if (buffer == 0) fatal_error("malloc failed");

  fat_seek_to_cluster(fs, de->start_cluster);
  fread(buffer, de->size, 1, fs->fd);
  buffer[de->size] = 0;

  return buffer;
}
