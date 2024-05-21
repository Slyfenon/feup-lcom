#include "game.h"

int16_t x = 500;
int16_t y = 400;

int16_t lastX = 500;
int16_t lastY = 400;

int score = 0;
int timeLeft = 30;

Position positions[] = {{10, 300}, {110, 300}, {210, 300}, {310, 300}, {410, 100}};
Direction directions[] = {RIGHT, RIGHT, RIGHT, RIGHT, LEFT};

Target* targets[5];

void (initGame)() {
    for (int i = 0; i < 5; i++) {
        targets[i] = createTarget(positions[i], directions[i]);
    }
}

uint16_t (getX)() {
    return (uint16_t)x;
}

uint16_t (getY)() {
    return (uint16_t)y;
}

uint16_t (getXOfTarget)(int i) {
    return (uint16_t)targets[i]->pos.x;
}

uint16_t (getYOfTarget)(int i) {
    return (uint16_t)targets[i]->pos.y;
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

void (updateTargets)() {
    for (int i = 0; i < 5; i++) {
        if (targets[i]->dir == RIGHT) targets[i]->pos.x = targets[i]->pos.x + 5;
        else if (targets[i]->dir == LEFT) targets[i]->pos.x = targets[i]->pos.x - 5;

        if (targets[i]->pos.x > 1100) targets[i]->pos.x = 0;
        else if (targets[i]->pos.x < -20) targets[i]->pos.x = 1000;
    }
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
