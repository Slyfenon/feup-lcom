#include <lcom/lcf.h>
#include "sprite.h"
#include "../resources/font/font.xpm"
#include "../resources/font/play.xpm"
#include "../resources/font/quit.xpm"


typedef enum Option {
  SINGLEPLAYER,
  MULTIPLAYER,
  QUIT
} Option;

Sprite* play;
Sprite* quit;

int getCurrentOption();

void setCurrentOption(int option);

void increaseCurrentOption();

void decreaseCurrentOption();

void createPlay();

void createQuit();

void initMenu();
