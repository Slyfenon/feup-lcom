#include <lcom/lcf.h>
#include <lcom/lab3.h>

#include <stdint.h>
#include "keyboard.h"
#include "i8042.h"

int keyboard_hook_id = KEYBOARD_IRQ;
uint8_t keyboardBytes[2];
uint8_t keyboardIndexArray = 0;
uint8_t stat;

int (kbc_subscribe_int)(uint8_t *bit_no) {
    *bit_no = keyboard_hook_id;
    if (sys_irqsetpolicy(KEYBOARD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &keyboard_hook_id) != OK) {
        printf("sys_irqsetpolicy inside %s", __func__);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int (kbc_unsubscribe_int)() {
    if (sys_irqrmpolicy(&keyboard_hook_id) != OK) {
        printf("sys_irqrmpolicy inside %s", __func__);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void (kbc_ih)() {
    uint8_t byte;

    if (util_sys_inb(KBC_CMD_REG, &stat) != OK) keyboardIndexArray = 0;

    else if (util_sys_inb(KBC_OUT_BUF, &byte) != OK) keyboardIndexArray = 0;

    else if ((stat & (KBC_PAR_ERR | KBC_TO_ERR)) != 0) keyboardIndexArray = 0;

    else {
        keyboardBytes[keyboardIndexArray] = byte;
        keyboardIndexArray++;
    }
}
