#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int hook_id = 0;
int counter = 0;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  uint8_t st;
  
  timer_get_conf(timer, &st);

  st &= (BIT(0) | BIT(1) | BIT(2) | BIT(3));

  st |= TIMER_LSB_MSB;

  st |= (timer << 6);

  sys_outb(TIMER_CTRL, st);

  uint16_t count = TIMER_FREQ / freq;
  uint8_t lsb, msb;
  util_get_LSB(count, &lsb);
  util_get_MSB(count, &msb);

  sys_outb(TIMER_0 + timer, lsb);
  sys_outb(TIMER_0 + timer, msb);

  return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
  *bit_no = hook_id;
  return sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id);
}

int (timer_unsubscribe_int)() {
  return sys_irqrmpolicy(&hook_id);
}

void (timer_int_handler)() {
  counter++;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  uint8_t rbc = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);
  
  if (sys_outb(TIMER_CTRL, rbc) != 0) {
    return 1;
  }

  if (util_sys_inb(TIMER_0 + timer, st) != 0) {
    return 1;
  }

  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {
  
  union timer_status_field_val conf;

  switch (field)
  {
    case tsf_all:
      conf.byte = st;
      break;
    case tsf_initial:
      conf.in_mode = (st & TIMER_LSB_MSB) >> 4;
      break;
    case tsf_mode:
      conf.count_mode = (st & (BIT(3) | BIT(2) | BIT(1))) >> 1;
      break;
    case tsf_base:
      conf.bcd = (st & TIMER_BCD);
      break;
  }

  return timer_print_config(timer, field, conf);
}
