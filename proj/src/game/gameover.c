#include "gameover.h"

/**
 * DRAW FUNCTIONS
 */

void (draw_GameOverScore)() {
  int player1Score = getPlayerScore(getPlayer1());
  int player2Score = getPlayerScore(getPlayer2());

  if(player1Score >= player2Score) {
    draw_sprite(win, MAX_X / 2, MAX_Y / 2);
  }
  else{
    draw_sprite(lost, MAX_X / 2, MAX_Y / 2);
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
