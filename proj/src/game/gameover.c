#include "gameover.h"

/**
 * DRAW FUNCTIONS
 */

void (draw_GameOverScore)() {
  int tempScore = getPlayerScore(getPlayer1());
  for (int i = 0; i < 5; i++) {
    uint8_t digit = tempScore % 10;
    tempScore /= 10;
    draw_sprite(numbers[digit], MAX_X / 2 + 100 - i * 50, MAX_Y / 2);
  }

    if(isMultiplayer()) {
    int tempScore2 = getPlayerScore(getPlayer2());
    for (int i = 0; i < 5; i++) {
      uint8_t digit = tempScore2 % 10;
      tempScore2 /= 10;
      draw_sprite(numbers[digit], MAX_X / 2 + 100 - i * 50, MAX_Y / 2 + 100);
  }
  }
}



void (draw_gameover)(bool isDay) {
  if (isDay) {
    draw_background(dayDesert->map);
  }
  else {
    draw_background (nightDesert->map);
  }
  draw_sprite(GameOver, MAX_X / 2, 100);
  draw_GameOverScore();
  draw_sprite(GameOverESC, MAX_X / 2, MAX_Y - 60);

  vg_page_flipping();
}
