#include "game.h"

int16_t x = 500;
int16_t y = 400;

int16_t lastX = 500;
int16_t lastY = 400;

int score = 0;
int timeLeft = 30; 

uint16_t (getX)() {
    return (uint16_t)x;
}

uint16_t (getY)() {
    return (uint16_t)y;
}

uint16_t (getLastX)() {
    return (uint16_t)lastX;
}

uint16_t (getLastY)() {
    return (uint16_t)lastY;
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

void (updateLastPositionDrawn)() {
    lastX = x;
    lastY = y;
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
