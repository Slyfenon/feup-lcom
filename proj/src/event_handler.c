#include "event_handler.h"
#include "devices/graphics/graphics.h"
#include "game/sprite.h"

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
  }

  return GAME;
}

void (draw_game)() {
  draw_back(desert->map);

  draw_sprite(aim, getX(), getY());
  draw_sprite(targettt, 200, 300);
}
