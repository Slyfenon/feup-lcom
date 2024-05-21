#ifndef TARGET_H
#define TARGET_H

#include <lcom/lcf.h>
#include "position.h"

typedef struct {
    Position pos;
    bool active;
    Direction dir;
} Target;


Target* createTarget(Position pos, Direction dir);

#endif
