#include "target.h"

Target* createTarget(Position pos, Direction dir) {
    Target* target = (Target*)malloc(sizeof(Target));

    target->pos = pos;
    target->dir = dir;

    return target;
}

