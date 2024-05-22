#include "event_handler.h"
#include "devices/graphics/graphics.h"
#include "game/sprite.h"

uint32_t color = 0;

void(handle_timer)(State state) {
  if (state == GAME) {
    updateTargets();
    draw_game();
  }
  if (state == MENU) {
    draw_menu();
  }
}

State(handle_keyboard)(State state, uint8_t *keyboardBytes) {
  printf("keyboardBytes[0]: %x\n", keyboardBytes[0]);
  if (state == GAME) {
    // não há nada ainda
  }
  if (state == MENU) {
    if (keyboardBytes[0] == 0x1C) {
      switch (getCurrentOption()) {
        case 0:
          initGame();
          return GAME;
          break;
        default:
          break;
      }
    }
    if (keyboardBytes[0] == 0xE0 && keyboardBytes[1] == 0x48) {
      increaseCurrentOption();
    }
    if (keyboardBytes[0] == 0xE0 && keyboardBytes[1] == 0x50) {
      decreaseCurrentOption();
    }
    return MENU;
  }
  return GAME;
}

State(handle_mouse)(State state, struct mousePacket *pp) {
  if (state == GAME) {
    addToX(pp->delta_x);
    addToY(pp->delta_y);

    if (pp->lb) {
      checkAllCollisions();
    }

    return GAME;
  }
  if (state == MENU) {
    // não há nada ainda
    return MENU;
  }

  return MENU;
}

void(draw_targets)() {
  for (int i = 0; i < NUM_TARGETS; i++) {
    if (isActiveTarget(i))
      draw_sprite(target, getXOfTarget(i), getYOfTarget(i));
  }
}

void(draw_game)() {
  draw_background(desert->map);

  draw_targets();
  draw_sprite(aim, getX(), getY());

  vg_page_flipping();
}

void draw_menu() {

  createPlay();

 for(int i = 0; i < 4; i++){
    draw_sprite(play[i], 100 + i*100, 100);
  }

}
