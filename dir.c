#include <string.h>

#include "dir.h"

void fat_read_filename(char * output, struct fat_dir_entry * de) {
  int len;
  char name[FAT_FILENAME_LENGTH + 1], extension[FAT_EXTENSION_LENGTH + 1];
  char * p;

  /* name, null-terminated, whitespace stripped */
  len = FAT_FILENAME_LENGTH;
  while (de->name[len - 1] == 0x20 && len > 0) len--;
  memmove(name, de->name, len);
  name[len] = 0;

  /* extension, null-terminated, whitespace stripped */
  len = FAT_EXTENSION_LENGTH;
  while (de->extension[len - 1] == 0x20 && len > 0) len--;
  memmove(extension, de->extension, len);
  extension[len] = 0;

  /* write name */
  p = stpcpy(output, name);

  /* write extension */
  if (*extension) {
    *p++ = '.';
    strcpy(p, extension);
  }
}

int fat_dir_entry_exists(struct fat_dir_entry * de) {
  /* 0x00: null entry, 0xE5: marked as deleted */
  return !(*de->name == 0x00 || *de->name == 0xE5);
}

int fat_is_volume_label(struct fat_dir_entry * de) {
  return (de->attributes & 0x08) == 0x08;
}

int fat_is_file(struct fat_dir_entry * de) {
  /* not volume label, not directory */
  return (de->attributes & 0x18) == 0;
}

int fat_is_dir(struct fat_dir_entry * de) {
  /* not volume label, is directory */
  return (de->attributes & 0x18) == 0x10;
}
