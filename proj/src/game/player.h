#ifndef __PLAYER_H
#define __PLAYER_H
#include <lcom/lcf.h>
#include "position.h"

typedef struct {
  Position pos;
  uint16_t score;
  bool canShoot;
} Player;

Player* (createPlayer)();

int16_t (getPlayerX)(Player* player);

int16_t (getPlayerY)(Player* player);

uint16_t (getPlayerScore)(Player* player);

bool (getPlayerCanShoot)(Player* player);

void (setPlayerX)(Player* player, uint16_t x);

void (setPlayerY)(Player* player, uint16_t y);

void (setPlayerScore)(Player* player, uint16_t score);

void (setPlayerCanShoot)(Player* player, bool canShoot);

void (destroyPlayer)(Player* player);

#endif
