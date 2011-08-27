#include "time.h"

void fat_read_date(struct fat_date * date, uint16_t bitfield) {
  date->day = bitfield & 0x1F; /* 5 bits: 0..4 */
  date->month = (bitfield >> 5) & 0x0F; /* 4 bits: 5..8 */
  date->year = ((bitfield >> 9) & 0x7F) + 1980; /* 7 bits: 9..15 */
}

void fat_read_time(struct fat_time * time, uint16_t bitfield) {
  time->second = (bitfield & 0x1F) * 2; /* 5 bits: 0..4 */
  time->minute = (bitfield >> 5) & 0x3F; /* 6 bits: 5..10 */
  time->hour = (bitfield >> 11) & 0x1F; /* 5 bits: 11..15 */
}
