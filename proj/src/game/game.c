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
    for (int i = 0; i < NUM_TARGETS; i++) {
        targets[i] = createTarget(positions[i], directions[i]);
    }
}

int16_t (getX)() {
    return x;
}

int16_t (getY)() {
    return y;
}

int16_t (getXOfTarget)(int i) {
    return targets[i]->pos.x;
}

int16_t (getYOfTarget)(int i) {
    return targets[i]->pos.y;
}

bool (isActiveTarget)(int i) {
    return targets[i]->active;
}

void (setActiveTarget)(int i, bool value) {
    targets[i]->active = value;
}


int16_t (getLastX)() {
    return lastX;
}

int16_t (getLastY)() {
    return lastY;
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
    for (int i = 0; i < NUM_TARGETS; i++) {
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

bool checkCollisionWithTarget(int i) {
    int distance = (x - getXOfTarget(i)) * (x - getXOfTarget(i)) + (y - getYOfTarget(i)) * (y - getYOfTarget(i));

    if (distance < 300) {
        setActiveTarget(i, false);
        return true;
    }

    return false;
}

bool checkAllCollisions() {
    for (int i = NUM_TARGETS - 1; i >= 0; i--) {
        if (checkCollisionWithTarget(i)) return true;
    }

    return false;
}

void (endGame)() {
    x = 500;
    y = 400;
    score = 0;
    timeLeft = 30; 
}
