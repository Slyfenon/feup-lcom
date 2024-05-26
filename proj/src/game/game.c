#include "game.h"

int16_t x = 500;
int16_t y = 400;

int16_t lastX = 500;
int16_t lastY = 400;

int score;
int timeLeft;
bool canShoot = true;
bool canSlowTime = true;

Target *targets[NUM_TARGETS];

void(initGame)() {
  score = 0;
  timeLeft = 10 * 60;

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
  for (int i = 0; i < NUM_TARGETS; i++) {
    if (targets[i]->dir == RIGHT)
      targets[i]->pos.x = targets[i]->pos.x + 5;
    else if (targets[i]->dir == LEFT)
      targets[i]->pos.x = targets[i]->pos.x - 5;

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

void(updateTimeLeft)() {
  timeLeft--;
}

bool(endTime)() {
  return (timeLeft == 0);
}

bool checkCollisionWithTarget(int i) {
  int distance = (x - getXOfTarget(i)) * (x - getXOfTarget(i)) + (y - getYOfTarget(i)) * (y - getYOfTarget(i));

  if (distance < TARGET_RADIUS_2) {
    setActiveTarget(i, false);

    if (distance < TARGET_RADIUS_2_CENTER) {
      score += 50;
    }

    else if (distance < TARGET_RADIUS_2_MIDDLE) {
      score += 25;
    }

    else {
      score += 10;
    }

    printf("Score: %u\n", score);

    return true;
  }

  return false;
}

bool checkAllCollisions() {
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
  score = 0;
  timeLeft = 10 * 60;
}

void(draw_targets)() {
  for (int i = 0; i < NUM_TARGETS; i++) {
    if (isActiveTarget(i))
      draw_sprite(target, getXOfTarget(i), getYOfTarget(i));
  }
}

void(draw_game)() {

  draw_targets();
  draw_sprite(aim, getX(), getY());
  draw_sprite(scoreSprite, MAX_X - 400, MAX_Y - 65);

  int score = getScore();

  int numDigits = 0;
  int tempScore = score;
  while (tempScore != 0) {
    tempScore /= 10;
    numDigits++;
  }

  int startX = MAX_X - 30;

  tempScore = score;
  for (int i = numDigits - 1; i >= 0; i--) {
    int digit = tempScore % 10;
    draw_sprite(numbers[digit], startX, MAX_Y - 65);
    startX -= 50;
    tempScore /= 10;
  }

  int tempTime = getTimeLeft() / 60;
  int numDigitsTime = 0;
  while (tempTime != 0) {
    tempTime /= 10;
    numDigitsTime++;
  }

  startX = MAX_X / 2;
  tempTime = getTimeLeft() / 60;
  for (int i = numDigitsTime ; i >= 0; i--) {
    int digit = tempTime % 10;
    draw_sprite(numbers[digit], startX, MAX_Y - 65);
    startX -= 50;
    tempTime /= 10;
  }
}
