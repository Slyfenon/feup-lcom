#include "game.h"

int16_t x = 500;
int16_t y = 400;
int score = 0;
int timeLeft = 30; 

uint16_t (getX)() {
    return (uint16_t)x;
}

uint16_t (getY)() {
    return (uint16_t)y;
}

void (addToX)(int16_t delta_x) {
    x += delta_x;

    if (x < 0) x = 0;
    if (x > MAX_X) x = MAX_X;
}

void (addToY)(int16_t delta_y) {
    y -= delta_y;

    if (y < 0) y = 0;
    if (y > MAX_Y) y = MAX_Y;
}

int (getScore)() {
    return score;
}

void (endGame)() {
    x = 500;
    y = 400;
    score = 0;
    timeLeft = 30; 
}
