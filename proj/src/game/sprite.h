#ifndef SPRITE_H
#define SPRITE_H
#include "../devices/graphics/graphics.h"
#include "../resources/sprites/aim.xpm"
#include "../resources/sprites/desert.xpm"
#include "../resources/sprites/target.xpm"
#include "../resources/font/score.xpm"
#include "../resources/font/numbers.xpm"

#define TRANSPARENT 0xFF000000

typedef struct Sprite{
    uint16_t height, width;
    uint32_t* map;
} Sprite; 

Sprite* desert;
Sprite* aim;
Sprite* target;
Sprite* scoreSprite;
Sprite* numbers[10];

Sprite* create_sprite(xpm_map_t xpm);

int draw_sprite(Sprite* sprite, int x, int y);

int erase_sprite(Sprite* sprite, int x, int y);

int load_sprites();

#endif

