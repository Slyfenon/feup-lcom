#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>

/* IRQ numbers */
#define KEYBOARD_IRQ 1
#define MOUSE_IRQ 12


/* I/O port adresses */
#define KBC_ST_REG 0X64
#define KBC_CMD_REG 0x64
#define KBC_OUT_BUF 0X60


/* KBC errors */
#define KBC_PAR_ERR BIT(7)
#define KBC_TO_ERR BIT(6)

/* KBC I/O buffer full */
#define KBC_IBF BIT(1)
#define KBC_OBF BIT(0)

/* KBC Commands*/
#define WRITE_CMD_BYTE 0X60
#define READ_CMD_BYTE 0X20
#define KBC_ENABLE_INT BIT(0)
#define WRITE_BYTE_MOUSE 0XD4

/* Mouse Commands */
#define MOUSE_GET_DEVICE_ID 0xF2
#define MOUSE_SET_SAMPLE_RATE 0xF3
#define MOUSE_ENABLE_DATA_REPORT 0xF4
#define MOUSE_DISABLE_DATA_REPORT 0xF5

/* PS/2 Mouse Data Packet */
#define Y_OVF BIT(7)
#define X_OVF BIT(6)
#define MSB_Y_DELTA BIT(5)
#define MSB_X_DELTA BIT(4)
#define VALIDATION_BIT BIT(3)
#define MIDDLE_BUTTON BIT(2)
#define RIGHT_BUTTON BIT(1)
#define LEFT_BUTTON BIT(0)

/* Commands auxs */
#define ACK 0xFA
#define MAX_TRIES 20
#define DELAY 20000

/* Mouse ids */
#define PS2_MOUSE 0X00
#define INTELLIMOUSE 0X03

#endif
