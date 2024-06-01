#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdbool.h>
#include <stdint.h>

int (kbc_subscribe_int)(uint8_t *bit_no);

int (kbc_unsubscribe_int)();

bool (kbc_scancode_is_done)();

void (kbc_get_scancode)(uint8_t* scancode);

#endif /* KEYBOARD_H */
