#ifndef POSITION_H
#define POSITION_H
#include <lcom/lcf.h>

typedef struct {
  int16_t x;
  int16_t y;
} Position;

typedef enum {
  LEFT,
  RIGHT,
  UP,
  DOWN,
} Direction;
#endif
