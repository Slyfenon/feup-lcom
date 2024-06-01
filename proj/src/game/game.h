#ifndef _GAME_H_
#define _GAME_H_
#include <lcom/lcf.h>

#include "dynamite.h"
#include "player.h"
#include "position.h"
#include "sprite.h"
#include "target.h"

#define MAX_X 1151
#define MAX_Y 863
#define NUM_TARGETS (NUM_TARGET_LINES * NUM_TARGETS_PER_LINE)
#define NUM_TARGET_LINES 3
#define NUM_TARGETS_PER_LINE 7


bool(isMultiplayer)();
void(setMultiplayer)(bool value);

/**
 * GENERIC GAME FUNCTIONS
 */

void(initGame)(bool multiplayer);

void(endGame)();

// GAME UPDATES

void(updateTimes)();

void(updateTargets)();

void(updateDynamite)();

// SHOTS AND COLLISIONS

int(checkAllCollisions)(Player *player);

int(checkCollisionWithTargets)(Player *player);

int(checkCollisionWithTarget)(Player *player, int i);

bool(checkCollisionWithDynamite)(Player *player);

// SLOW TIME

bool(canSlowTime)();

void(setSlowTime)();

void(endSlowTime)();

/**
 * GETTERS AND SETTERS OF GAME VARIABLES
 */

Player *(getPlayer1) ();

Player *(getPlayer2) ();

// PLAYER POSITION
void(addToX)(Player *player, int16_t delta_x);

void(addToY)(Player *player, int16_t delta_y);

// TARGETS
int16_t(getFallCounterOfTarget)(int i);

void(incrementFallCounterOfTarget)(int i);

bool(isActiveTarget)(int i);

void(setActiveTarget)(int i, bool value);

// DYNAMITE

bool(isActiveDynamite)();

void(setActiveDynamite)(bool value);

// SCORE

void(addToScore)(Player *player, int value);

void(subractToScore)(Player *player, int value);

// TIME

int(getTimeLeft)();

bool(endTime)();

/**
 * DRAW FUNCTIONS
 */

void(draw_game)(bool isDay);

void draw_aim(Player *player);

void(draw_lines)();

void(draw_targets)();

void(draw_dynamite)();

void(draw_score)();

void(draw_timeLeft)();

#endif
