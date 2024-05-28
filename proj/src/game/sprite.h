#ifndef SPRITE_H
#define SPRITE_H
#include "../devices/graphics/graphics.h"
#include "../resources/sprites/aim.xpm"
#include "../resources/sprites/clock.xpm"
#include "../resources/sprites/dayDesert.xpm"
#include "../resources/sprites/dynamite.xpm"
#include "../resources/sprites/nightDesert.xpm"
#include "../resources/sprites/target.xpm"
#include "../resources/font/numbers.xpm"
#include "../resources/font/score.xpm"

#define TRANSPARENT 0xFF000000

typedef struct Sprite {
  uint16_t height, width;
  uint32_t *map;
} Sprite;

Sprite *dayDesert;
Sprite *nightDesert;
Sprite *aim;
Sprite *target;
Sprite *dynamite;
Sprite *clockIcon;
Sprite *scoreSprite;
Sprite *numbers[10];

Sprite *create_sprite(xpm_map_t xpm);

int draw_sprite(Sprite *sprite, int x, int y);

int erase_sprite(Sprite *sprite, int x, int y);

int load_sprites();

#endif
