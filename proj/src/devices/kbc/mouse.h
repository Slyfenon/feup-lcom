#ifndef MOUSE_H
#define MOUSE_H

#include <stdbool.h>
#include <stdint.h>
#include <lcom/lab4.h>

#include "../../utils.h"

int (mouse_subscribe_int)(uint8_t *bit_no);

int (mouse_unsubscribe_int)();

bool (mouse_packet_is_done)();

void (mouse_get_packet)(struct mousePacket *pp);

int (kbc_write_command)(uint8_t cmd);

int (write_byte_to_mouse)(uint8_t byte);

int (mouse_enable_data_reporting_mine)();

int (mouse_disable_data_reporting)();

int (mouse_set_sample_rate)(uint8_t rate);

int (write_get_device_id_to_mouse)(uint8_t* id);

int (get_mouse_id)(uint8_t* id);

int (mouse_enable_scrolling)();

#endif
