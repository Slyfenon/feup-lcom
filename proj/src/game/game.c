#include "game.h"

int16_t x;
int16_t y;

int score;
int timeLeft;
bool canShoot;
bool slowTime;
int timerSlowTime;

bool checkExplosion = false;
int explosionX;
int explosionY;
int frameExplosion = 0;

bool isUpdatingDynamites = false;

Target *targets[NUM_TARGETS];
Dynamite *dynamite;

/**
 * GENERIC GAME FUNCTIONS
 */

void(initGame)() {
  x = 500;
  y = 400;
  resetScore();
  timeLeft = 30 * 60;
  timerSlowTime = 0;
  canShoot = true;
  slowTime = false;

  int i = 0;

  int targetX = -100;
  int targetY = 100;

  while (i < NUM_TARGETS) {
    for (int j = 0; j < NUM_TARGETS_PER_LINE; j++) {
      targets[i] = createTarget(targetX, targetY, (targetY % 100) ? LEFT : RIGHT);
      i++;
      targetX += 200;
    }

    targetX = -100;
    targetY += 150;
  }

  dynamite = createDynamite(100, -100, DOWN);
}

void(endGame)() {
  // TODO
  // METER OS DELETE
}

// GAME UPDATES

void(updateTimes)() {
  timeLeft--;
  if (timerSlowTime > 0)
    timerSlowTime--;

  if (slowTime && (timerSlowTime == 0)) {
    endSlowTime();
  }
}

void(updateTargets)() {
  int step = slowTime ? 2 : 5;

  for (int i = 0; i < NUM_TARGETS; i++) {
    if (targets[i]->dir == RIGHT)
      targets[i]->pos.x = targets[i]->pos.x + step;
    else if (targets[i]->dir == LEFT)
      targets[i]->pos.x = targets[i]->pos.x - step;

    if (targets[i]->pos.x > 1200) {
      targets[i]->pos.x = -200;
      targets[i]->active = true;
      targets[i]->fallCounter = 0;
    }

    else if (targets[i]->pos.x < -200) {
      targets[i]->pos.x = 1200;
      targets[i]->active = true;
      targets[i]->fallCounter = 0;
    }
  }
}

void(updateDynamite)() {
  int step = slowTime ? 2 : 5;

  if (!isUpdatingDynamites) {
    dynamite->pos.x = ((x + y) * timeLeft) % MAX_X; // pseudorandom
    isUpdatingDynamites = true;
  }

  dynamite->pos.y += step;
  if (getYOfDynamite() > 900) {
    dynamite->pos.y = -100;
    subractToScore(10);
    isUpdatingDynamites = false;
  }
}

// SHOTS AND COLLISIONS

bool(getCanShoot)() {
  return canShoot;
}

void(setCanShoot)(bool value) {
  canShoot = value;
}

bool(checkAllCollisions)() {

  if (checkCollisionWithDynamite())
    return true;

  if (checkCollisionWithTargets()) {
    return true;
  }

  return false;
}

bool(checkCollisionWithTargets)() {
  if ((y > 46) && (y < 154)) {
    for (int i = 0; i < 7; i++) {
      if (checkCollisionWithTarget(i))
        return true;
    }
  }

  else if ((y > 196) && (y < 304)) {
    for (int i = 7; i < 14; i++) {
      if (checkCollisionWithTarget(i))
        return true;
    }
  }

  else if ((y > 346) && (y < 454)) {
    for (int i = 14; i < 21; i++) {
      if (checkCollisionWithTarget(i))
        return true;
    }
  }

  return false;
}

bool(checkCollisionWithTarget)(int i) {
  int distance = (x - getXOfTarget(i)) * (x - getXOfTarget(i)) + (y - getYOfTarget(i)) * (y - getYOfTarget(i));

  if (distance < TARGET_RADIUS_2) {
    setActiveTarget(i, false);

    if (distance < TARGET_RADIUS_2_CENTER) {
      addToScore(10);
    }

    else if (distance < TARGET_RADIUS_2_MIDDLE) {
      addToScore(5);
    }

    else {
      addToScore(1);
    }

    return true;
  }

  return false;
}

bool(checkCollisionWithDynamite)() {
  int distance = (x - getXOfDynamite()) * (x - getXOfDynamite()) + (y - getYOfDynamite()) * (y - getYOfDynamite());

  if (distance < TARGET_RADIUS_2) {
    setActiveDynamite(false);
    checkExplosion = true;
    explosionX = getXOfDynamite();
    explosionY = getYOfDynamite();
    isUpdatingDynamites = false;
    dynamite->pos.y = -100;
    dynamite->active = true;
    return true;
  }

  return false;
}

// SLOW TIME

bool(canSlowTime)() {
  return (!slowTime && (timerSlowTime == 0));
}

void(setSlowTime)() {
  if (canSlowTime()) {
    slowTime = true;
    timerSlowTime = 5 * 60;
  }
}

void(endSlowTime)() {
  slowTime = false;
  timerSlowTime = 10 * 60;
}

/**
 * GETTERS AND SETTERS OF GAME VARIABLES
 */

// PLAYER POSITION

int16_t(getX)() {
  return x;
}

int16_t(getY)() {
  return y;
}

void(addToX)(int16_t delta_x) {
  x += delta_x;

  if (x < 0)
    x = 0;
  if (x > MAX_X)
    x = MAX_X;
}

void(addToY)(int16_t delta_y) {
  y -= delta_y;

  if (y < 0)
    y = 0;
  if (y > MAX_Y)
    y = MAX_Y;
}

// TARGETS

int16_t(getXOfTarget)(int i) {
  return targets[i]->pos.x;
}

int16_t(getYOfTarget)(int i) {
  return targets[i]->pos.y;
}

int16_t(getFallCounterOfTarget)(int i) {
  return targets[i]->fallCounter;
}

void(incrementFallCounterOfTarget)(int i) {
  targets[i]->fallCounter++;
}

bool(isActiveTarget)(int i) {
  return targets[i]->active;
}

void(setActiveTarget)(int i, bool value) {
  targets[i]->active = value;
}

// DYNAMITE

bool(isActiveDynamite)() {
  return dynamite->active;
}

void(setActiveDynamite)(bool value) {
  dynamite->active = value;
}

int16_t(getXOfDynamite)() {
  return dynamite->pos.x;
}

int16_t(getYOfDynamite)() {
  return dynamite->pos.y;
}

// SCORE

int(getScore)() {
  return score;
}

void(addToScore)(int value) {
  score += value;

  if (score > 99999)
    score = 99999;
}

void(subractToScore)(int value) {
  if (score <= value)
    score = 0;

  else
    score -= value;
}

void(resetScore)() {
  score = 0;
}

// TIME

int(getTimeLeft)() {
  return timeLeft;
}

bool(endTime)() {
  return (timeLeft == 0);
}

/**
 * DRAW FUNCTIONS
 */

void(draw_game)(bool isDay) {
  if (isDay) {
    draw_background(dayDesert->map);
  }
  else {
    draw_background(nightDesert->map);
  }
  draw_lines();
  draw_targets();
  draw_dynamite();
  draw_sprite(aim, getX(), getY());
  draw_sprite(scoreSprite, MAX_X - 400, MAX_Y - 65);
  draw_score();
  draw_timeLeft();

  if (canSlowTime())
    draw_sprite(clockIcon, 70, MAX_Y - 70);

  vg_page_flipping();
}

void(draw_lines)() {

  int lineY = 100 + TARGET_RADIUS - 15;
  for (int i = 0; i < 3; i++) {
    vg_draw_rectangle(0, lineY, MAX_X, 5, 0x696969);
    lineY += 150;
  }
}

void(draw_targets)() {
  for (int i = 0; i < NUM_TARGETS; i++) {
    if (isActiveTarget(i))
      draw_sprite(target, getXOfTarget(i), getYOfTarget(i));

    else if (targets[i]->fallCounter < 12) {
      draw_sprite(fall[getFallCounterOfTarget(i) / 4], getXOfTarget(i), getYOfTarget(i));
      targets[i]->fallCounter++;
    }
  }
}

void(draw_dynamite)() {
  if (isActiveDynamite()) {
    draw_sprite(dynamiteIcon, getXOfDynamite(), getYOfDynamite());
  }

  if (checkExplosion) {
    draw_sprite(explosion[frameExplosion / 5], explosionX, explosionY);
    frameExplosion++;

    if (frameExplosion == 25) {
      checkExplosion = false;
      frameExplosion = 0;
    }
  }
}

void(draw_score)() {
  int numDigits = 0;
  int tempScore = score;
  while (tempScore != 0) {
    tempScore /= 10;
    numDigits++;
  }

  if (numDigits == 0)
    numDigits = 1;

  int startX = MAX_X - 30;

  tempScore = score;
  for (int i = numDigits - 1; i >= 0; i--) {
    int digit = tempScore % 10;
    draw_sprite(numbers[digit], startX, MAX_Y - 65);
    startX -= 50;
    tempScore /= 10;
  }
}

void(draw_timeLeft)() {
  int tempTime = getTimeLeft() / 60;
  int numDigitsTime = 0;
  while (tempTime != 0) {
    tempTime /= 10;
    numDigitsTime++;
  }

  if (numDigitsTime == 0)
    numDigitsTime = 1;

  int startX = MAX_X / 2;
  tempTime = getTimeLeft() / 60;
  for (int i = numDigitsTime; i > 0; i--) {
    int digit = tempTime % 10;
    draw_sprite(numbers[digit], startX, MAX_Y - 65);
    startX -= 50;
    tempTime /= 10;
  }
}
