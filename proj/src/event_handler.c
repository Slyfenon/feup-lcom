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
  if (state == ENDGAME) {
    // não há nada ainda
  }
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

  if (state == ENDGAME) {
    return ENDGAME;
  }

  return MENU;
}

void(draw_targets)() {
  for (int i = 0; i < NUM_TARGETS; i++) {
    if (isActiveTarget(i))
      draw_sprite(target, getXOfTarget(i), getYOfTarget(i));
  }
}

int checkTime() {
  if (readTime() != 0) {
    printf("Error in readTime inside: %s\n", __func__);
    return EXIT_FAILURE;
  }

  if (timeRTC.hours > 19 || timeRTC.hours < 7) {
    draw_background(nightDesert->map);
  }
  else {
    draw_background(dayDesert->map);
  }
  return EXIT_SUCCESS;
}

void(draw_game)() {
  if (checkTime() != 0) {
    printf("Error in checkTime inside: %s\n", __func__);
    return;
  }

  draw_targets();
  draw_sprite(aim, getX(), getY());
  draw_sprite(scoreSprite, MAX_X - 400, MAX_Y - 65);

  int score = getScore();

  int numDigits = 0;
  int tempScore = score;
  while (tempScore != 0) {
    tempScore /= 10;
    numDigits++;
  }

  int startX = MAX_X - 30;

  tempScore = score;
  for (int i = numDigits - 1; i >= 0; i--) {
    int digit = tempScore % 10;
    draw_sprite(numbers[digit], startX, MAX_Y - 65);
    startX -= 50;
    tempScore /= 10;
  }

  vg_page_flipping();
}

void draw_menu() {

  if (checkTime() != 0) {
    printf("Error in checkTime inside: %s\n", __func__);
    return;
  }

  int startX = MAX_X - 170;

  for (int i = 0; i < 2; i++) {
    draw_sprite(hours[i], startX, MAX_Y - 65);
    startX -= 50;
  }

  draw_sprite(dots, startX + 145, MAX_Y - 65);

  startX = MAX_X - 30;
  for (int i = 0; i < 2; i++) {
    draw_sprite(minutes[i], startX, MAX_Y - 65);
    startX -= 50;
  }

  if (nightDesert == NULL) {
    printf("Error in load_sprites inside: %s\n", __func__);
    return;
  }

  createPlay();
  createQuit();

  draw_sprite(play, MAX_X / 2, 100);
  draw_sprite(quit, MAX_X / 2, 200);

  switch (getCurrentOption()) {
    case SINGLEPLAYER:
      vg_draw_rectangle(MAX_X / 2 - 120, 140, 240, 10, 0x000000);
      break;
    case QUIT:
      vg_draw_rectangle(MAX_X / 2 - 120, 240, 240, 10, 0x000000);
      break;
    default:
      break;
  }

  vg_page_flipping();
}
