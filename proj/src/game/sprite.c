#include "sprite.h"

Sprite* create_sprite(xpm_map_t xpm) {

  Sprite* sprite = (Sprite*) malloc (sizeof(Sprite));
  if(sprite == NULL) return NULL;

  xpm_image_t img;
  sprite->map = (uint32_t*)xpm_load(xpm, XPM_8_8_8_8, &img);
  sprite->height = img.height;
  sprite->width = img.width;

  if(sprite->map == NULL) {
    free(sprite);
    return NULL;
  }

  return sprite;
}

int draw_sprite(Sprite* sprite, int x, int y) { 
  uint32_t* aux = sprite->map;
  int xBeginning = x - (sprite->width / 2);
  int yBeginning = y - (sprite->height / 2);

  for (int i = 0 ; i < sprite->height ; i++) {
    for (int j = 0 ; j < sprite->width ; j++) {
      if (*aux == TRANSPARENT) {
        aux++;
        continue;
      }
      
      if (vg_draw_pixel(xBeginning + j, yBeginning + i, *aux)) return EXIT_FAILURE;
      aux++;
    }
  }
  return EXIT_SUCCESS; 
}

int erase_sprite(Sprite* sprite, int x, int y) {
  int width = sprite->width;
  int height = sprite->height;

  uint32_t aux;

  for (int i = 0 ; i < height; i++) {
    for (int j = 0 ; j < width; j++) {
      if ((y + i) >= desert->height) continue;
      if ((x + j) >= desert->width) continue;

      aux = desert->map[(y+i)*desert->width + (x + j)];
      if (vg_draw_pixel(x + j, y + i, aux)) return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}

int load_sprites() {
  aim = create_sprite(aim_xpm);
  desert = create_sprite(desert_xpm);
  target = create_sprite(target_xpm);

  return EXIT_SUCCESS;
}

