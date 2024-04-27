#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdbool.h>
#include <stdint.h>
#include <lcom/lab5.h>

#include "vbe.h"

int (set_graphics_mode)(uint16_t mode);
int (set_frame_buffer)(uint16_t mode);

int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);

int (vg_size_xpm)(xpm_map_t xpm);
int (vg_load_xpm)(xpm_map_t xpm, uint8_t** map, xpm_image_t* img);
int (vg_draw_xpm)(uint8_t** map, xpm_image_t* img, uint16_t x, uint16_t y);
int (vg_load_and_draw_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y);

uint32_t (R)(uint32_t color);
uint32_t (G)(uint32_t color);
uint32_t (B)(uint32_t color);

#endif
