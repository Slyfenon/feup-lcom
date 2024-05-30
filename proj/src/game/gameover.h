#include "sprite.h"
#include "game.h"
#include "../resources/font/gameover.xpm"
#include "../resources/font/gameoverEsc.xpm"
#include <lcom/lcf.h>

Sprite *GameOver;
Sprite *GameOverESC; 

void load_gameover();

void draw_GameOverScore();

void draw_gameover();
