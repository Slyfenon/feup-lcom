#ifndef __GAME_H
#define __GAME_H
#include "dynamite.h"
#include "sprite.h"
#include "target.h"
#include <lcom/lcf.h>

#define MAX_X 1151
#define MAX_Y 862
#define NUM_TARGETS 21
#define NUM_TARGETS_PER_LINE 7

/**
 * GENERIC GAME FUNCTIONS
*/

void (initGame)();

void (endGame)();


// GAME UPDATES

void (updateTimes)();

void (updateTargets)();

void (updateDynamite)();


// SHOTS AND COLLISIONS

bool (getCanShoot)();

void (setCanShoot)(bool value);

bool (checkAllCollisions)();

bool (checkCollisionWithTargets)();

bool (checkCollisionWithTarget)(int i);

bool (checkCollisionWithDynamite)();


// SLOW TIME

bool (canSlowTime)();

void (setSlowTime)();

void (endSlowTime)();



/**
 * GETTERS AND SETTERS OF GAME VARIABLES
*/

// PLAYER POSITION

int16_t (getX)();

int16_t (getY)();

void (addToX)(int16_t delta_x);

void (addToY)(int16_t delta_y);


// TARGETS

int16_t (getXOfTarget)(int i);

int16_t (getYOfTarget)(int i);

int16_t (getFallCounterOfTarget)(int i);

void (incrementFallCounterOfTarget)(int i);

bool (isActiveTarget)(int i);

void (setActiveTarget)(int i, bool value);


// DYNAMITE

bool (isActiveDynamite)();

void (setActiveDynamite)(bool value);

int16_t (getXOfDynamite)();

int16_t (getYOfDynamite)();


// SCORE

int (getScore)();

void (addToScore)(int value);

void (subractToScore)(int value);

void (resetScore)();


// TIME

int (getTimeLeft)();

bool (endTime)();



/**
 * DRAW FUNCTIONS 
*/

void (draw_game)();

void (draw_lines)();

void (draw_targets)();

void (draw_dynamite)();

void (draw_score)();

void (draw_timeLeft)();

#endif
