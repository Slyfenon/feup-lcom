#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdbool.h>
#include <stdint.h>
#include <lcom/lab5.h>

#include "vbe.h"

/** @brief graphics graphics
 * @{
 *
 * Functions for using the graphics card
 */
int (set_graphics_mode)(uint16_t mode);
int (set_frame_buffer)(uint16_t mode);

int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);

int (vg_page_flipping)();

int (vg_reset_current_buffer)();

uint8_t* (get_actual_buffer)();

int (get_vram_size)();

int (draw_background)(uint32_t* map);

#endif /* GRAPHICS_H */
