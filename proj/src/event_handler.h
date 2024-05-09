#include <lcom/lcf.h>

#include "game/game.h"
#include "utils.h"

typedef enum State {
    MENU,
    GAME,
    ENDGAME
} State;

State (handle_keyBoard)(enum State state, uint8_t* keyboardBytes);

State (handle_mouse)(enum State state, struct mousePacket* pp);
