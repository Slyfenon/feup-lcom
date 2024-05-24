#ifndef TARGET_H
#define TARGET_H

#include <lcom/lcf.h>
#include "position.h"

#define TARGET_RADIUS 54
#define TARGET_RADIUS_2 2916  //TARGET_RADIUS²
#define TARGET_RADIUS_2_CENTER 400
#define TARGET_RADIUS_2_MIDDLE 1600

typedef struct {
    Position pos;
    bool active;
    Direction dir;
} Target;

Target* createTarget(int x, int y, Direction dir);

#endif
