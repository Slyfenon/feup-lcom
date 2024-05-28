#include "dynamite.h"

Dynamite* createDynamite(int x, int y, Direction dir) {
    Dynamite* dynamite = (Dynamite*)malloc(sizeof(Dynamite));
    Position* pos = (Position*)malloc(sizeof(Position));

    pos->x = x;
    pos->y = y;

    dynamite->pos = *pos;
    dynamite->dir = dir;
    dynamite->active = true;
    dynamite->explosionFrame = 0;

    return dynamite;
}
