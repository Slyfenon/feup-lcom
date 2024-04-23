#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdbool.h>
#include <stdint.h>

int (kbc_subscribe_int)(uint8_t *bit_no);

int (kbc_unsubscribe_int)();

#endif
