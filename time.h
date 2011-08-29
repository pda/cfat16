#pragma once
#include <stdint.h>

struct fat_date {
  unsigned short int day;
  unsigned short int month;
  unsigned short int year;
};

struct fat_time {
  unsigned short int second;
  unsigned short int minute;
  unsigned short int hour;
};

void fat_read_date(struct fat_date *, uint16_t bitfield);
void fat_read_time(struct fat_time *, uint16_t bitfield);
