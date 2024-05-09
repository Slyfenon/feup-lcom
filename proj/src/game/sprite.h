#include "../devices/graphics/graphics.h"
#include "../resources/sprites/aim.xpm"

typedef struct Sprite{
    uint16_t height, width;
    uint32_t* map;
} Sprite; 

Sprite* aim;

Sprite* create_sprite(xpm_map_t xpm);

int draw_sprite(Sprite* sprite, int x, int y);

int load_sprites();
