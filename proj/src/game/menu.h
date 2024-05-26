#include "../devices/rtc/rtc.h"
#include "../resources/font/font.xpm"
#include "../resources/font/play.xpm"
#include "../resources/font/quit.xpm"
#include "sprite.h"
#include "game.h"
#include <lcom/lcf.h>

typedef enum Option {
  SINGLEPLAYER,
  MULTIPLAYER,
  QUIT
} Option;

Sprite *play;
Sprite *quit;
Sprite *dots;
Sprite *hours[2];
Sprite *minutes[2];

rtc_time timeRTC;

int getCurrentOption();

void setCurrentOption(int option);

void increaseCurrentOption();

void decreaseCurrentOption();

void createPlay();

void createQuit();

int readTime();

void draw_menu();
