#include <lcom/lcf.h>

#include <stdint.h>

int (util_sys_inb)(int port, uint8_t *value) {
  uint32_t aux;
  sys_inb(port, &aux);
  *value = aux & 0xFF;

  return 0;
}
