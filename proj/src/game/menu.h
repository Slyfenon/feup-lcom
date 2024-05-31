#ifndef __MENU_H
#define __MENU_H
#include "../devices/rtc/rtc.h"
#include "../resources/font/font.xpm"
#include "game.h"
#include "sprite.h"
#include <lcom/lcf.h>

typedef enum Option {
  SINGLEPLAYER,
  MULTIPLAYER,
  QUIT
} Option;

Sprite *hours[2];
Sprite *minutes[2];

rtc_time timeRTC;

/**
 * GETTERS AND SETTERS OF MENU VARIABLES
 */

int(getCurrentOption)();

void(setCurrentOption)(int option);

void(increaseCurrentOption)();

void(decreaseCurrentOption)();

/**
 * TIME FUNCTION
 */

int(readTime)();

/**
 * DRAW FUNCTIONS
 */

void(draw_menu)();
#endif
