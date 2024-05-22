#include "game.h"

int16_t x = 500;
int16_t y = 400;

int16_t lastX = 500;
int16_t lastY = 400;

int score = 0;
int timeLeft = 30;

Position positions[] = {{100, 100}, {300, 100}, {500, 100}, {700, 100}, {900, 100}, {1100, 100}, {100, 250}, {300, 250}, {500, 250}, {700, 250}, {900, 250}, {1100, 250}, {100, 400}, {300, 400}, {500, 400}, {700, 400}, {900, 400}, {1100, 400}};

Target* targets[NUM_TARGETS];

void (initGame)() {
    int i = 0;

    while (i < NUM_TARGETS) {
        for (int j = 0; j < NUM_TARGETS_PER_LINE; j++) {
            targets[i] = createTarget(positions[i], RIGHT);
            i++;
        }

        if (i == NUM_TARGETS) break;

        for (int j = 0; j < NUM_TARGETS_PER_LINE; j++) {
            targets[i] = createTarget(positions[i], LEFT);
            i++;
        }
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

        if (targets[i]->pos.x > 1200) {
            targets[i]->pos.x = -200;
            targets[i]->active = true;
        }

        else if (targets[i]->pos.x < -200) {
            targets[i]->pos.x = 1200;
            targets[i]->active = true;
        }    
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

    if (distance < TARGET_RADIUS_2) {
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
