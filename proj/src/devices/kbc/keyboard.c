#include <lcom/lcf.h>
#include <lcom/lab3.h>

#include <stdint.h>
#include "keyboard.h"
#include "i8042.h"

int keyboard_hook_id = KEYBOARD_IRQ;
uint8_t stat;
uint8_t scancode;

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
    if (util_sys_inb(KBC_CMD_REG, &stat) != OK) scancode = KEYBOARD_ERROR;

    else if (util_sys_inb(KBC_OUT_BUF, &scancode) != OK) scancode = KEYBOARD_ERROR;

    else if ((stat & (KBC_PAR_ERR | KBC_TO_ERR)) != 0) scancode = KEYBOARD_ERROR;
}
