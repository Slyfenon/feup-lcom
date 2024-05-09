#include <lcom/lcf.h>
#include "position.h"

typedef struct{
    Position pos;
    bool active;
    enum Direction dir;
    xpm_image_t body;

} Target;


Target* createTarget(Position pos, enum Direction dir);
