#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
    /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_unsubscribe_int)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

void (timer_int_handler)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);
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
