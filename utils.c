#include <string.h>

#include "utils.h"

void fat_string_copy(char * output, char * input, int length) {
  memset(output, '\0', length + 1);
  strncpy(output, input, length);
}
