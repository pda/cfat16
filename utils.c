#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"

/**
 * Various strings in FAT aren't null-terminated.
 * strncpy() on it's own doesn't guarantee null-terminated output.
 * strlcpy() does, but it is non-standard and not present in glibc.
 * output buffer must be at least length+1 bytes.
 */
void fat_string_copy(char * output, char * input, int length) {
  memset(output, '\0', length + 1);
  strncpy(output, input, length);
}

void fatal_error(char * message) {
  printf("ERROR: %s\n", message);
  exit(EXIT_FAILURE);
}
