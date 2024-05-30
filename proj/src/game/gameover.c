#include "gameover.h"

void load_gameover() {
  GameOver = create_sprite(gameover_xpm);
  GameOverESC = create_sprite(gameoverEsc_xpm);
}

void draw_GameOverScore() {
  int tempScore = getScore();
  for (int i = 0; i < 5; i++) {
    uint8_t digit = tempScore % 10;
    tempScore /= 10;
    draw_sprite(numbers[digit], MAX_X / 2 + 100 - i * 50, MAX_Y / 2);
  }
}

void draw_gameover() {
  load_gameover();
  draw_sprite(GameOver, MAX_X / 2, 100);
  draw_GameOverScore();
  draw_sprite(GameOverESC, MAX_X / 2, MAX_Y - 60);
}
