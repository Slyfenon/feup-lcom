#include <lcom/lcf.h>
#include <lcom/lab4.h>

#include <stdint.h>
#include "mouse.h"
#include "i8042.h"

int mouse_hook_id = MOUSE_IRQ;
extern uint8_t bytes[4];
extern uint8_t indexArray;
extern uint8_t stat;

int (mouse_subscribe_int)(uint8_t *bit_no) {
    *bit_no = mouse_hook_id;
    if (sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_hook_id) != 0) return 0;

    return 0;
}

int (mouse_unsubscribe_int)() {
    if (sys_irqrmpolicy(&mouse_hook_id) != 0) return 1;

    return 0;
}

void (mouse_ih)() {
    uint8_t byte;

    if (util_sys_inb(KBC_OUT_BUF, &byte) != 0) indexArray = 0;

    else if (stat & (KBC_PAR_ERR | KBC_TO_ERR)) indexArray = 0;

    else if ((indexArray == 0) && ((byte & VALIDATION_BIT) == 0)) {
        indexArray = 0;
    }

    else {
        bytes[indexArray] = byte;
        indexArray++;
    }
}

int (kbc_write_command)(uint8_t cmd) {
    int tries = MAX_TRIES;

    while (tries) {
        if (util_sys_inb(KBC_CMD_REG, &stat) != 0) return 1;

        if ((stat & KBC_IBF) == 0) {
            if (sys_outb(KBC_CMD_REG, cmd) != 0) return 1;
            return 0;
        }

        tries--;
        tickdelay(micros_to_ticks(DELAY));
    }

    return 1;
}

int (write_byte_to_mouse)(uint8_t byte) {
    int tries = MAX_TRIES;
    uint8_t ack;

    while (tries) {
        if (kbc_write_command(WRITE_BYTE_MOUSE) != 0) return 1;

        tickdelay(micros_to_ticks(DELAY));

        if (util_sys_inb(KBC_CMD_REG, &stat) != 0) return 1;

        if ((stat & KBC_IBF) == 0) {
            if (sys_outb(KBC_OUT_BUF, byte) != 0) return 1;

            tickdelay(micros_to_ticks(DELAY));

            if (util_sys_inb(KBC_OUT_BUF, &ack) != 0) return 1;

            if (ack == ACK) return 0;
        }

        tries--;
        tickdelay(micros_to_ticks(DELAY));
    }

    return 1;
}

int (mouse_enable_data_reporting_mine)() {
    int tries = MAX_TRIES;

    while (tries) {
        if (write_byte_to_mouse(MOUSE_ENABLE_DATA_REPORT) == 0) {
            return 0;
        }

        else {
            tries--;
            tickdelay(micros_to_ticks(DELAY));
        }
    }

    return 0;
}

int (mouse_disable_data_reporting)() {
    int tries = MAX_TRIES;

    while (tries) {
        if (write_byte_to_mouse(MOUSE_DISABLE_DATA_REPORT) == 0) {
            return 0;
        }

        else {
            tries--;
            tickdelay(micros_to_ticks(DELAY));
        }
    }

    return 0;
}

void (mouse_parse_packet)(struct packet *pp) {
    pp->bytes[0] = bytes[0];
    pp->bytes[1] = bytes[1];
    pp->bytes[2] = bytes[2];
    pp->rb = bytes[0] & RIGHT_BUTTON;
    pp->mb = bytes[0] & MIDDLE_BUTTON;
    pp->lb = bytes[0] & LEFT_BUTTON;
    pp->delta_x = (bytes[0] & MSB_X_DELTA) ? (0xFF00 | bytes[1]) : bytes[1];
    pp->delta_y = (bytes[0] & MSB_Y_DELTA) ? (0xFF00 | bytes[2]) : bytes[2];
    pp->x_ov = bytes[0] & X_OVF;
    pp->y_ov = bytes[0] & Y_OVF;
}

int (mouse_set_sample_rate)(uint8_t rate) {
    int tries = MAX_TRIES;

    while (tries) {
        tries--;

        if (write_byte_to_mouse(MOUSE_SET_SAMPLE_RATE) != 0) continue;;

        tickdelay(micros_to_ticks(DELAY));

        if (write_byte_to_mouse(rate) == 0) return 0;
    }

    return 1;
}

// can't use the generic write_byte_to_mouse because the output (device id) overwrites the ack
int (write_get_device_id_to_mouse)(uint8_t* id) {
    int tries = MAX_TRIES;

    while (tries) {
        if (kbc_write_command(WRITE_BYTE_MOUSE) != 0) return 1;

        tickdelay(micros_to_ticks(DELAY));

        if (util_sys_inb(KBC_CMD_REG, &stat) != 0) return 1;

        if ((stat & KBC_IBF) == 0) {
            if (sys_outb(KBC_OUT_BUF, MOUSE_GET_DEVICE_ID) != 0) return 1;

            tickdelay(micros_to_ticks(DELAY));

            if (util_sys_inb(KBC_OUT_BUF, id) == 0) return 0;
        }

        tries--;
        tickdelay(micros_to_ticks(DELAY));
    }

    return 1;
}

int (get_mouse_id)(uint8_t* id) {
    int tries = MAX_TRIES;

    while (tries) {
        tries--;

        if (write_get_device_id_to_mouse(id) != 0) continue;

        tickdelay(micros_to_ticks(DELAY));

        tries = 1;
        break;
    }

    if (!tries) return 1;

    return 0;
}

int (enable_scrolling)(){
    uint8_t id = 0;

    if (mouse_set_sample_rate(200) != 0) return 1;

    if (mouse_set_sample_rate(100) != 0) return 1;

    if (mouse_set_sample_rate(80) != 0) return 1;

    if (get_mouse_id(&id) != 0) return 1;

    if (id != INTELLIMOUSE) {
        printf("Failed to enable scrolling\n");
        return 1;
    }

    return 0;
}
