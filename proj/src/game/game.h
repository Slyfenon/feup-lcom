#include <lcom/lcf.h>
#include "target.h"

#define MAX_X 1151
#define MAX_Y 862

void (initGame)();

uint16_t (getX)();

uint16_t (getY)();

uint16_t (getLastX)();

uint16_t (getLastY)();

void (addToX)(int16_t delta_x);

void (addToY)(int16_t delta_y);

void (updateLastPositionDrawn)();

int (getScore)();

int (decrementAndReturnTimeLeft)();

void (endGame)();
