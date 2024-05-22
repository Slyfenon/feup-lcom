#include <lcom/lcf.h>
#include "sprite.h"
#include "../resources/font/p.xpm"
#include "../resources/font/l.xpm"
#include "../resources/font/a.xpm"
#include "../resources/font/y.xpm"

typedef enum Option {
  SINGLEPLAYER,
  MULTIPLAYER,
  QUIT
} Option;

Sprite* play[4];

int getCurrentOption();

void setCurrentOption(int option);

void increaseCurrentOption();

void decreaseCurrentOption();

void createPlay();

void initMenu();
