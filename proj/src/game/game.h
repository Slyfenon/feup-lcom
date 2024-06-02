#ifndef _GAME_H_
#define _GAME_H_
#include <lcom/lcf.h>

#include "dynamite.h"
#include "player.h"
#include "position.h"
#include "sprite.h"
#include "target.h"

#define MAX_X 1151 /** @brief Maximum x coordinate of the screen */
#define MAX_Y 863 /** @brief Maximum y coordinate of the screen */
#define NUM_TARGETS (NUM_TARGET_LINES * NUM_TARGETS_PER_LINE) /** @brief Number of targets in the game */
#define NUM_TARGET_LINES 3 /** @brief Number of lines of targets in the game */
#define NUM_TARGETS_PER_LINE 7 /** @brief Number of targets per line in the game */



/** @brief Return is the game is in multiplayer mode. */
bool(isMultiplayer)();

/** @brief Set the game to multiplayer mode .
  * 
  * @param value - true if the game is in multiplayer mode, false otherwise.
  */
void(setMultiplayer)(bool value);

/**
 * GENERIC GAME FUNCTIONS
 */

/** @brief Initialize the game.
  * Initializes the game variables and the players .
  * @param multiplayer - true if the game is in multiplayer mode, false otherwise.
  */
void(initGame)(bool multiplayer);

/** @brief Resets the game.
  * Resets the game variables and the players .
  */
void(endGame)();

// GAME UPDATES

/** @brief Updates game countdown.
  * Decreases the time left in the game. If the time is over, ends the game
  */
void(updateTimes)();

/** @brief Updates game targets
  * Updates the position of the targets in the game.
  * If slow time is active, updates the targets at a slower pace.  
  */
void(updateTargets)();

/** @brief Updates game dynamite
  * Updates the position of the dynamite in the game.
  * If slow time is active, updates the dynamite at a slower pace.  
  */
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
