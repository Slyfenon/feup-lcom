#ifndef __GAME_H
#define __GAME_H
#include "sprite.h"
#include "target.h"
#include <lcom/lcf.h>

#define MAX_X 1151
#define MAX_Y 862
#define NUM_TARGETS 21
#define NUM_TARGETS_PER_LINE 7

void(initGame)();

int16_t(getX)();

int16_t(getY)();

int16_t(getXOfTarget)(int i);

int16_t(getYOfTarget)(int i);

bool(isActiveTarget)(int i);

void(setActiveTarget)(int i, bool value);

int16_t(getLastX)();

int16_t(getLastY)();

void(addToX)(int16_t delta_x);

void(addToY)(int16_t delta_y);

void(updateTargets)();

void(updateLastPositionDrawn)();

int(getScore)();

int(getTimeLeft)();

void(updateTimes)();

bool(endTime)();

bool checkCollisionWithTarget(int i);

bool checkAllCollisions();

bool getCanShoot();

void setCanShoot(bool value);

void(endGame)();

void (setSlowTime)();

void (endSlowTime)();

void(draw_game)();

void(draw_targets)();

void (draw_score)();

void (draw_timeLeft)();

#endif
