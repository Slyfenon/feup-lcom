#ifndef SPRITE_H
#define SPRITE_H
#include "../devices/graphics/graphics.h"
#include "../resources/font/gameover.xpm"
#include "../resources/font/gameoverEsc.xpm"
#include "../resources/font/numbers.xpm"
#include "../resources/font/play.xpm"
#include "../resources/font/quit.xpm"
#include "../resources/font/score.xpm"
#include "../resources/sprites/aim.xpm"
#include "../resources/sprites/clock.xpm"
#include "../resources/sprites/dayDesert.xpm"
#include "../resources/sprites/dynamite.xpm"
#include "../resources/sprites/explosion.xpm"
#include "../resources/sprites/fall.xpm"
#include "../resources/sprites/nightDesert.xpm"
#include "../resources/sprites/target.xpm"

#define TRANSPARENT 0xFF000000

typedef struct Sprite {
  uint16_t height, width;
  uint32_t *map;
} Sprite;

Sprite *dayDesert;
Sprite *nightDesert;
Sprite *aim;
Sprite *target;
Sprite *fall[3];
Sprite *dynamiteIcon;
Sprite *explosion[5];
Sprite *clockIcon;
Sprite *scoreSprite;
Sprite *numbers[10];
Sprite *play;
Sprite *quit;
Sprite *dots;
Sprite *GameOver;
Sprite *GameOverESC;

Sprite *create_sprite(xpm_map_t xpm);

int draw_sprite(Sprite *sprite, int x, int y);

int erase_sprite(Sprite *sprite, int x, int y);

void loadMenu();

void loadGameOver();

int load_sprites();

int delete_sprites();

#endif
