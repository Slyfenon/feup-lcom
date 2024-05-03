#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdbool.h>
#include <stdint.h>
#include <lcom/lab5.h>

#include "vbe.h"

int (set_graphics_mode)(uint16_t mode);
int (set_frame_buffer)(uint16_t mode);

int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);

int (vg_page_flipping)();

#endif
