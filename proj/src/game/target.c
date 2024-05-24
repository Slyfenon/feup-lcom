#include "target.h"

Target* createTarget(int x, int y, Direction dir) {
    Target* target = (Target*)malloc(sizeof(Target));
    Position* pos = (Position*)malloc(sizeof(Position));

    pos->x = x;
    pos->y = y;

    target->pos = *pos;
    target->dir = dir;
    target->active = true;

    return target;
}
