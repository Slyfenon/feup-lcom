#include <lcom/lcf.h>

#include "uart.h"
#include <stdint.h>

unsigned short base_addr;
int ser_hook_id;

static queue_t *tx_queue = NULL;
static queue_t *rx_queue = NULL;

queue_t *(ser_get_tx_queue) () {
  return tx_queue;
}

queue_t *(ser_get_rx_queue) () {
  return rx_queue;
}

int(ser_subscribe_int)(uint8_t *bit_no) {
  if (bit_no == NULL) {
    printf("Null pointer inside %s\n", __func__);
    return EXIT_FAILURE;
  }
  *bit_no = ser_hook_id;
  if (sys_irqsetpolicy(ser_hook_id, IRQ_REENABLE | IRQ_EXCLUSIVE, &ser_hook_id) != EXIT_SUCCESS) {
    printf("Error in sys_irqsetpolicy inside %s\n", __func__);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int(ser_unsubscribe_int)() {
  if (sys_irqrmpolicy(&ser_hook_id) != EXIT_SUCCESS) {
    printf("Error in sys_irqrmpolicy inside %s\n", __func__);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int(ser_write_reg)(uint8_t reg, uint8_t data) {
  if (sys_outb(base_addr + reg, data) != EXIT_SUCCESS) {
    printf("Error in sys_outb inside %s\n", __func__);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int(ser_read_reg)(uint8_t reg, uint8_t *data) {
  if (util_sys_inb(base_addr + reg, data) != EXIT_SUCCESS) {
    printf("Error in util_sys_inb inside %s\n", __func__);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int(ser_conf)(unsigned short addr, conf_t config) {
  switch (addr) {
    case SER_COM1:
      base_addr = addr;
      ser_hook_id = SER_COM1_IRQ;
      break;
    case SER_COM2:
      base_addr = addr;
      ser_hook_id = SER_COM2_IRQ;
      break;
    default:
      printf("Invalid base address inside %s\n", __func__);
      return EXIT_FAILURE;
  }
  if (ser_set_bit_rate(config.bit_rate) != 0) {
    printf("Error in ser_set_bit_rate inside %s\n", __func__);
    return EXIT_FAILURE;
  }
  if (ser_set_line_ctrl(&config) != 0) {
    printf("Error in ser_set_line_ctrl inside %s\n", __func__);
    return EXIT_FAILURE;
  }
  if (ser_enable_fifo() != 0) {
    printf("Error in ser_enable_fifo inside %s\n", __func__);
    return EXIT_FAILURE;
  }
  if (ser_enable_int() != 0) {
    printf("Error in ser_enable_int inside %s\n", __func__);
    return EXIT_FAILURE;
  }
  tx_queue = create_queue(QUEUE_SIZE, sizeof(uint8_t));
  rx_queue = create_queue(QUEUE_SIZE, sizeof(uint8_t));
  if (tx_queue == NULL || rx_queue == NULL) {
    printf("Error initializing queues inside %s\n", __func__);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int(ser_set_bit_rate)(unsigned int bit_rate) {
  uint8_t lcr, lsb, msb;
  bit_rate = SER_MAX_FREQ / bit_rate;
  if (util_get_LSB(bit_rate, &lsb) != 0) {
    printf("Error in util_get_LSB inside %s\n", __func__);
    return EXIT_FAILURE;
  }
  if (util_get_MSB(bit_rate, &msb) != 0) {
    printf("Error in util_get_MSB inside %s\n", __func__);
    return EXIT_FAILURE;
  }
  if (ser_read_reg(SER_LCR, &lcr) != 0) {
    printf("Error in ser_read_reg inside %s\n", __func__);
    return EXIT_FAILURE;
  }
  if (ser_write_reg(SER_LCR, lcr | SER_LCR_DLAB) != 0) {
    printf("Error in ser_set_bit_rate inside %s\n", __func__);
    return EXIT_FAILURE;
  }
  if (ser_write_reg(SER_DLL, lsb) != 0) {
    printf("Error in ser_write_reg inside %s\n", __func__);
    return EXIT_FAILURE;
  }
  if (ser_write_reg(SER_DLM, msb) != 0) {
    printf("Error in ser_write_reg inside %s\n", __func__);
    return EXIT_FAILURE;
  }
  if (ser_write_reg(SER_LCR, lcr & ~SER_LCR_DLAB) != 0) {
    printf("Error in ser_set_bit_rate inside %s\n", __func__);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int(ser_set_line_ctrl)(conf_t *config) {
  lcr_t lcr;
  lcr.value = 0;
  lcr.word_length = SER_LCR_WORD_SIZE(config->no_bits);
  lcr.stop_bits = config->stop_bits;
  lcr.parity = config->parity;
  if (ser_write_reg(SER_LCR, lcr.value) != 0) {
    printf("Error in ser_write_reg inside %s\n", __func__);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int(ser_enable_fifo)() {
  if (ser_write_reg(SER_FCR, SER_FCR_EN_FIFO | SER_FCR_CLR_RX_FIFO | SER_FCR_CLR_TX_FIFO | SER_FCR_TRIGGER_1) != 0) {
    printf("Error in ser_write_reg inside %s\n", __func__);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int(ser_disable_fifo)() {
  if (ser_write_reg(SER_FCR, 0x00) != 0) {
    printf("Error in ser_write_reg inside %s\n", __func__);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int(ser_enable_int)() {
  if (ser_write_reg(SER_IER, SER_IER_RX_INT | SER_IER_TX_INT | SER_IER_LINE_ST) != 0) {
    printf("Error in ser_write_reg inside %s\n", __func__);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int(ser_disable_int)() {
  if (ser_write_reg(SER_IER, 0x00) != 0) {
    printf("Error in ser_write_reg inside %s\n", __func__);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int(ser_send_byte)(uint8_t b) {
  if (ser_write_reg(SER_THR, b) != 0) {
    printf("Error in ser_write_reg inside %s\n", __func__);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int(ser_receive_byte)(uint8_t *b) {
  if (b == NULL) {
    printf("Null pointer inside %s\n", __func__);
    return EXIT_FAILURE;
  }
  if (ser_read_reg(SER_RBR, b) != 0) {
    printf("Error in ser_read_reg inside %s\n", __func__);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int(ser_send_data)() {
  uint8_t lsr;
  uint8_t data;

  if (ser_read_reg(SER_LSR, &lsr) != 0) {
    printf("Error reading Line Status Register inside %s\n", __func__);
    return EXIT_FAILURE;
  }

  while (!queue_is_empty(tx_queue) && (lsr & SER_LSR_TX_RDY)) {
    if (queue_dequeue(tx_queue, &data) != 0) {
      printf("Error dequeuing data inside %s\n", __func__);
      return EXIT_FAILURE;
    }
    if (ser_send_byte(data) != 0) {
      printf("Error sending byte inside %s\n", __func__);
      return EXIT_FAILURE;
    }
    if (ser_read_reg(SER_LSR, &lsr) != 0) {
      printf("Error reading Line Status Register inside %s\n", __func__);
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}

int(ser_receive_data)() {
  uint8_t lsr;
  uint8_t data;

  if (ser_read_reg(SER_LSR, &lsr) != 0) {
    printf("Error reading Line Status Register inside %s\n", __func__);
    return EXIT_FAILURE;
  }

  while ((lsr & SER_LSR_RX_RDY)) {
    if (ser_receive_byte(&data) != 0) {
      printf("Error receiving byte inside %s\n", __func__);
      return EXIT_FAILURE;
    }
    if (queue_enqueue(rx_queue, &data) != 0) {
      printf("Error enqueuing data inside %s\n", __func__);
      return EXIT_FAILURE;
    }
    if (ser_read_reg(SER_LSR, &lsr) != 0) {
      printf("Error reading Line Status Register inside %s\n", __func__);
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}

void(ser_ih)() {
  uint8_t iir;

  if (ser_read_reg(SER_IIR, &iir) != 0) {
    printf("Error reading Interrupt Identification Register inside %s\n", __func__);
    return;
  }

  if (!(iir & SER_IIR_INT_NP)) {
    /* Interrupt Status: Pending (Interruption) */
    switch (iir & SER_IIR_INT_ID) {
      case SER_IIR_RX_INT:
        /* Received Data Available */
        if (ser_receive_data() != 0) {
          printf("Error receiving data inside %s\n", __func__);
          return;
        }
        break;
      case SER_IIR_TX_INT:
        /* Transmitter Empty */
        if (ser_send_data() != 0) {
          printf("Error sending data inside %s\n", __func__);
          return;
        }
        break;
      default:
        break;
    }
  }
}

int(ser_exit)() {
  if(ser_disable_int() != 0) {
    printf("Error disabling interrupts inside %s\n", __func__);
    return EXIT_FAILURE;
  }
  if(ser_disable_fifo() != 0) {
    printf("Error disabling FIFO inside %s\n", __func__);
    return EXIT_FAILURE;
  }
  if (queue_destroy(tx_queue) != 0 || queue_destroy(rx_queue) != 0) {
    printf("Error destroying queues inside %s\n", __func__);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

typedef enum {
  WAITING,
  MOUSE_INFO,
  KBD_INFO
} ser_info_t;

ser_info_t ser_info = WAITING;

struct mousePacket ser_mouse_packet;
uint8_t ser_scancode;
int ser_mouse_index = 0;

int(ser_get_mouse_packet)(struct mousePacket *pp) {
  if (pp == NULL) {
    printf("Null pointer inside %s\n", __func__);
    return EXIT_FAILURE;
  }
  pp = &ser_mouse_packet;
  return EXIT_SUCCESS;
}

int(ser_get_scancode)(uint8_t *scancode) {
  if (scancode == NULL) {
    printf("Null pointer inside %s\n", __func__);
    return EXIT_FAILURE;
  }
  *scancode = ser_scancode;
  return EXIT_SUCCESS;
}

int(ser_handle_start)() {
  uint8_t data;
  if(queue_dequeue(rx_queue, &data) != 0) {
    printf("Error dequeuing data inside %s\n", __func__);
    return EXIT_FAILURE;
  }
  if(data == WAITING) {
    ser_info = WAITING;
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

int(ser_read_data_from_rx_queue)() {
  uint8_t data;
  while (!queue_is_empty(rx_queue)) {
    queue_dequeue(rx_queue, &data);

    switch (ser_info) {
      case WAITING:
        if (data == MOUSE_INFO) {
          ser_info = MOUSE_INFO;
        }
        else if (data == KBD_INFO) {
          ser_info = KBD_INFO;
        }
        break;
      case MOUSE_INFO:
        ser_mouse_packet.bytes[ser_mouse_index] = data;
        ser_mouse_index++;
        if (ser_mouse_index == 3) {
          ser_mouse_index = 0;
          ser_mouse_packet.delta_x = (ser_mouse_packet.bytes[0] & MSB_X_DELTA) ? (0xFF00 | ser_mouse_packet.bytes[1]) : ser_mouse_packet.bytes[1];
          ser_mouse_packet.delta_y = (ser_mouse_packet.bytes[0] & MSB_Y_DELTA) ? (0xFF00 | ser_mouse_packet.bytes[2]) : ser_mouse_packet.bytes[2];
          ser_mouse_packet.lb = ser_mouse_packet.bytes[0] & LEFT_BUTTON;
          ser_info = WAITING;
        }
        break;
      case KBD_INFO:
        ser_scancode = data;
        ser_info = WAITING;
        break;
      default:
        break;
    }
    break;
  }

  return EXIT_SUCCESS;
}

int(ser_send_mouse_info_to_txqueue)(struct mousePacket *pp) {
  ser_info_t info = MOUSE_INFO;
  if (queue_enqueue(tx_queue, &info) != 0) {
    printf("Error enqueuing data inside %s\n", __func__);
    return EXIT_FAILURE;
  }
  if (queue_enqueue(tx_queue, &pp->bytes[0]) != 0) {
    printf("Error enqueuing data inside %s\n", __func__);
    return EXIT_FAILURE;
  }
  if (queue_enqueue(tx_queue, &pp->bytes[1]) != 0) {
    printf("Error enqueuing data inside %s\n", __func__);
    return EXIT_FAILURE;
  }
  if (queue_enqueue(tx_queue, &pp->bytes[2]) != 0) {
    printf("Error enqueuing data inside %s\n", __func__);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int(ser_send_scancode_to_txqueue)(uint8_t scancode) {
  ser_info_t info = KBD_INFO;
  if (queue_enqueue(tx_queue, &info) != 0) {
    printf("Error enqueuing data inside %s\n", __func__);
    return EXIT_FAILURE;
  }
  if (queue_enqueue(tx_queue, &scancode) != 0) {
    printf("Error enqueuing data inside %s\n", __func__);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int(ser_send_waiting_to_txqueue)() {
  ser_info_t info = WAITING;
  if (queue_enqueue(tx_queue, &info) != 0) {
    printf("Error enqueuing data inside %s\n", __func__);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
