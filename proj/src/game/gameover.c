#include "gameover.h"

/**
 * DRAW FUNCTIONS
 */

void draw_GameOverScore() {
  int tempScore = getScore();
  for (int i = 0; i < 5; i++) {
    uint8_t digit = tempScore % 10;
    tempScore /= 10;
    draw_sprite(numbers[digit], MAX_X / 2 + 100 - i * 50, MAX_Y / 2);
  }
}

void draw_gameover(bool isDay) {
  if (isDay) {
    draw_background(dayDesert->map);
  }
  else {
    draw_background(nightDesert->map);
  }
  draw_sprite(GameOver, MAX_X / 2, 100);
  draw_GameOverScore();
  draw_sprite(GameOverESC, MAX_X / 2, MAX_Y - 60);
}
