#include <lcom/lcf.h>
#include <stdint.h>

#include "util.h"
#include <stdint.h>

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  *lsb = (u_int8_t) (val & 0x00FF);
  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  *msb = (u_int8_t) ((val & 0xFF00) >> 8);
  return 0;
}

int (util_sys_inb)(int port, uint8_t *value) {
  uint32_t aux;
  sys_inb(port, &aux);
  *value = aux & 0xFF;

  return 0;
}
