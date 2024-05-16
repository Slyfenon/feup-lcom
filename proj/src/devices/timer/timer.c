#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int counter = 0;
int hook_id = TIMER0_IRQ;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  /* To be implemented by the students */
  uint8_t config;
  timer_get_conf(timer, &config);

  uint16_t counter = TIMER_FREQ / freq;
  uint8_t counter_MSB;
  uint8_t counter_LSB;

  util_get_LSB(counter, &counter_LSB);
  util_get_MSB(counter, &counter_MSB);

  config = config & 0x3F;
  if (timer == 1) config = config | 0x40;
  else if (timer == 2) config = config | 0x80;

   if ((counter_MSB == 0) || (counter_LSB == 0)) {
    config = config & 0xCF;

    if (counter_MSB == 0) {
      config = config | 0x10;
      util_sys_inb(TIMER_CTRL, &config);
      util_sys_inb(0x40 + timer, &counter_LSB);
    }

    else {
      config = config | 0x20;
      util_sys_inb(TIMER_CTRL, &config);
      util_sys_inb(0x40 + timer, &counter_MSB);
    }
  } 

  else {
    config = config | 0x30;
    sys_outb(TIMER_CTRL, config);
    sys_outb(0x40 + timer, counter_LSB);
    sys_outb(0x40 + timer, counter_MSB);
  }

  return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
  /* To be implemented by the students */
  *bit_no = hook_id;
  sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id);

  return 0;
}

int (timer_unsubscribe_int)() {
  /* To be implemented by the students */
  sys_irqrmpolicy(&hook_id);
  return 0;
}

void (timer_int_handler)() {
  /* To be implemented by the students */
  counter++;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  /* To be implemented by the students */

  uint8_t cw = TIMER_RB_CMD | TIMER_RB_SEL(timer) | TIMER_RB_COUNT_;
  sys_outb(TIMER_CTRL, cw);

  util_sys_inb(0x40 + timer, st);

  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {
  /* To be implemented by the students */
  union timer_status_field_val conf;

  switch (field) {
    case tsf_all: conf.byte = st; break;
    case tsf_initial: conf.in_mode = (st & TIMER_LSB_MSB) >> 4; break;
    case tsf_mode: conf.count_mode = (st & (BIT(1) | BIT(2) | BIT(3))) >> 1; break;
    case tsf_base: conf.bcd = (st & TIMER_BCD); break;
  }

  timer_print_config(timer, field, conf);

  return 0;
}
