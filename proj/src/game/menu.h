#ifndef __MENU_H
#define __MENU_H
#include "../devices/rtc/rtc.h"
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

int(readTime)(rtc_time *timeRTC);

/**
 * DRAW FUNCTIONS
 */

void(draw_menu)(bool isDay);
#endif
