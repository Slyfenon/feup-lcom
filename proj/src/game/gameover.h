#include "sprite.h"
#include "game.h"
#include "../resources/font/gameover.xpm"
#include "../resources/font/gameoverEsc.xpm"
#include <lcom/lcf.h>

Sprite *GameOver;
Sprite *GameOverESC; 

/**
 * @brief Loads the game over screen.
 * 
 * This function is responsible for loading the game over screen, which is displayed when the game ends.
 * It loads the individual elements of the screen, such as the game over text and the score.
 * 
 * @return void
 */
void load_gameover();

/**
 * Draws the game over score on the screen.
 * This function is responsible for displaying the final score
 * achieved by the player after the game is over.
 */
void draw_GameOverScore();

/**
 * @brief Draws the game over screen.
 * Draws all the elements of the game over screen, such as the game over text and the score.
*/
void draw_gameover();
