#include <lcom/lcf.h>

#include "game/game.h"
#include "game/menu.h"
#include "utils.h"

typedef enum State{
    MENU,
    GAME,
    ENDGAME
} State;

State (handle_keyboard)(State state, uint8_t* keyboardBytes);

State (handle_mouse)(State state, struct mousePacket* pp);

void (handle_timer)(State state);

void (draw_targets)();

void (draw_game)();

void (draw_menu)();

int (checkTime)();

void (draw_line)(int len, uint16_t color, int x, int y);
