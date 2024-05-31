#include "event_handler.h"
#include "devices/graphics/graphics.h"
#include "game/sprite.h"

void background() {
  if (timeRTC.hours > 19 || timeRTC.hours < 7) {
    draw_background(nightDesert->map);
  }
  else {
    draw_background(dayDesert->map);
  }
}

State(handle_timer)(State state) {
  if (state == GAME) {
    updateTimes();
    updateTargets();
    updateDynamite();
    background();
    draw_game();

    if (endTime()) {
      endGame();
      return GAMEOVER;
    }
  }
  if (state == MENU) {
    if (readTime() != 0) {
      printf("Error in checkTime inside: %s\n", __func__);
      delete_sprites();
      return ENDGAME;
    }
    background();
    draw_menu();
  }
  if (state == ENDGAME) {
    delete_sprites();
    return ENDGAME;
  }

  if (state == GAMEOVER) {
    background();
    draw_gameover();
    vg_page_flipping();
    return GAMEOVER;
  }

  return state;
}

State(handle_keyboard)(State state, uint8_t *keyboardBytes) {
  if (state == GAME) {
    if (keyboardBytes[0] == 0x81) {
      return MENU;
    }
  }
  if (state == MENU) {
    if (keyboardBytes[0] == 0x1C) {
      switch (getCurrentOption()) {
        case 0:
          initGame();
          return GAME;
        case 2:
          delete_sprites(); 
          return ENDGAME;
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
  if (state == GAMEOVER) {
    if (keyboardBytes[0] == 0x81) {
      return MENU;
    }
    return GAMEOVER;
  }
  return GAME;
}

State(handle_mouse)(State state, struct mousePacket *pp) {
  if (state == GAME) {
    addToX(pp->delta_x);
    addToY(pp->delta_y);

    if (pp->lb) {
      if (getCanShoot()) {
        checkAllCollisions();
        setCanShoot(false);
      }
    }
    else {
      setCanShoot(true);
    }

    if (pp->delta_scroll > 1) {
      setSlowTime();
    }

    return GAME;
  }
  if (state == MENU) {
    return MENU;
  }

  if (state == ENDGAME) {
    return ENDGAME;
  }

  if (state == GAMEOVER) {
    return GAMEOVER;
  }

  return MENU;
}
