#include "game.h"

int16_t x = 500;
int16_t y = 400;

int16_t lastX = 500;
int16_t lastY = 400;

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

void(initGame)() {

  if (score >= 0) {
    score = 0;
  }
  timeLeft = 30 * 60;
  timerSlowTime = 0;
  canShoot = true;
  slowTime = false;

  int i = 0;

  int x = -100;
  int y = 100;

  while (i < NUM_TARGETS) {
    for (int j = 0; j < NUM_TARGETS_PER_LINE; j++) {
      targets[i] = createTarget(x, y, (y % 100) ? LEFT : RIGHT);
      i++;
      x += 200;
    }

    x = -100;
    y += 150;
  }
  i = 0;

  dynamite = createDynamite(100, -100, DOWN);
}

int16_t(getX)() {
  return x;
}

int16_t(getY)() {
  return y;
}

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

bool isActiveDynamite() {
  return dynamite->active;
}

void setActiveDynamite(bool value) {
  dynamite->active = value;
}

bool(isActiveTarget)(int i) {
  return targets[i]->active;
}

void(setActiveTarget)(int i, bool value) {
  targets[i]->active = value;
}

int16_t(getLastX)() {
  return lastX;
}

int16_t(getLastY)() {
  return lastY;
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
  if (dynamite->pos.y > 900) {
    dynamite->pos.y = -100;
    if (score < 10)
      score = 0;
    else
      score -= 10;
    isUpdatingDynamites = false;
  }
}

void(updateLastPositionDrawn)() {
  lastX = x;
  lastY = y;
}

int(getScore)() {
  return score;
}

int(getTimeLeft)() {
  return timeLeft;
}

void(updateTimes)() {
  timeLeft--;
  if (timerSlowTime > 0)
    timerSlowTime--;

  if (slowTime && (timerSlowTime == 0)) {
    endSlowTime();
  }
}

bool(endTime)() {
  return (timeLeft == 0);
}

bool checkCollisionWithTarget(int i) {
  int distance = (x - getXOfTarget(i)) * (x - getXOfTarget(i)) + (y - getYOfTarget(i)) * (y - getYOfTarget(i));

  if (distance < TARGET_RADIUS_2) {
    setActiveTarget(i, false);

    if (distance < TARGET_RADIUS_2_CENTER) {
      score += 10;
    }

    else if (distance < TARGET_RADIUS_2_MIDDLE) {
      score += 5;
    }

    else {
      score += 1;
    }
    if (score > 999)
      score = 999;
    return true;
  }

  return false;
}

bool checkCollisionWithDynamite() {
  int distance = (x - dynamite->pos.x) * (x - dynamite->pos.x) + (y - dynamite->pos.y) * (y - dynamite->pos.y);

  if (distance < TARGET_RADIUS_2) {
    setActiveDynamite(false);
    checkExplosion = true;
    explosionX = dynamite->pos.x;
    explosionY = dynamite->pos.y;
    isUpdatingDynamites = false;
    dynamite->pos.y = -100;
    dynamite->active = true;
    return true;
  }

  return false;
}

bool checkAllCollisions() {

  if (checkCollisionWithDynamite())
    return true;

  for (int i = NUM_TARGETS - 1; i >= 0; i--) {
    if (checkCollisionWithTarget(i))
      return true;
  }

  return false;
}

bool getCanShoot() {
  return canShoot;
}

void setCanShoot(bool value) {
  canShoot = value;
}

void(endGame)() {
  x = 500;
  y = 400;
  timeLeft = 10 * 60;
}

void setSlowTime() {
  if (!slowTime && (timerSlowTime == 0)) {
    slowTime = true;
    timerSlowTime = 5 * 60;
  }
}

void endSlowTime() {
  slowTime = false;
  timerSlowTime = 10 * 60;
}

bool(canSlowTime)() {
  return (!slowTime && (timerSlowTime == 0));
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

void(draw_dynamites)() {
  if (isActiveDynamite()) {
    draw_sprite(dynamiteIcon, dynamite->pos.x, dynamite->pos.y);
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

void drawLines() {

  int lineY = 100 + TARGET_RADIUS - 15;
  for (int i = 0; i < 3; i++) {
    vg_draw_rectangle(0, lineY, MAX_X, 5, 0x696969);
    lineY += 150;
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

void(draw_game)() {
  drawLines();
  draw_targets();
  draw_dynamites();
  draw_sprite(aim, getX(), getY());
  draw_sprite(scoreSprite, MAX_X - 400, MAX_Y - 65);
  draw_score();
  draw_timeLeft();

  if (canSlowTime())
    draw_sprite(clockIcon, 70, MAX_Y - 70);
}
