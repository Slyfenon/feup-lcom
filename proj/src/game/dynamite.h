#ifndef DYNAMITE_H
#define DYNAMITE_H

#include <lcom/lcf.h>
#include "position.h"

#define DYNAMITE_X 106
#define DYNAMITE_Y 10


typedef struct {
    Position pos;
    bool active;
    Direction dir;
} Dynamite;

Dynamite* createDynamite(int x, int y, Direction dir);


#endif
