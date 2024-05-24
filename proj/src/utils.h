#ifndef UTILS_H
#define UTILS_H

#include <lcom/lcf.h>

struct mousePacket {
  uint8_t bytes[3]; // mouse packet raw bytes
  bool rb, mb, lb;  // right, middle and left mouse buttons pressed
  int16_t delta_x;  // mouse x-displacement: rightwards is positive
  int16_t delta_y;  // mouse y-displacement: upwards is positive
  bool x_ov, y_ov;  // mouse x-displacement and y-displacement overflows
  int8_t delta_scroll; // scroll displacement: with a touchpad upwards is postive, with a mouse upwards is negative 
};

int (util_sys_inb)(int port, uint8_t *value);

#endif
