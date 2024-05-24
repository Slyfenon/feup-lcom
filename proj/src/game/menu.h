#include <lcom/lcf.h>
#include "sprite.h"
#include "../resources/font/font.xpm"

typedef enum Option {
  SINGLEPLAYER,
  MULTIPLAYER,
  QUIT
} Option;

Sprite* play[4];
Sprite* quit[4];

int getCurrentOption();

void setCurrentOption(int option);

void increaseCurrentOption();

void decreaseCurrentOption();

void createPlay();

void createQuit();

void initMenu();
