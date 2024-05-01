#include "event_handler.h"
#include "devices/graphics/graphics.h"

uint32_t color = 0;

State (handle_keyBoard)(enum State state, uint8_t* keyboardBytes) {
    if (state == GAME) {
        // não há nada ainda
    }

    return GAME;
}

State (handle_mouse)(enum State state, struct mousePacket* pp) {
    if (state == GAME) {
        addToX(pp->delta_x);
        addToY(pp->delta_y);

        uint16_t x = getX();
        uint16_t y = getY(); 

        for (int i = 0; i < 50; i++) {
          for (int j = 0; j < 50; j++) {
            if (vg_draw_pixel(x + j, y + i, ++color) != OK) return EXIT_FAILURE;
          }
        }
    }

    return GAME;
}
