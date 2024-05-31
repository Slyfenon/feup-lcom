#ifndef RTC_H
#define RTC_H

#include <stdbool.h>
#include <stdint.h>

#define RTC_ADDR_REG 0x70
#define RTC_DATA_REG 0X71


#define RTC_IRQ 8

#define HOURS 4
#define MINUTES 2
#define SECONDS 0
#define RTC_REG_A 0x0A
#define RTC_REG_B 0x0B
#define RTC_REG_C 0x0C
#define RTC_REG_D 0x0D

#define BLOCKED_BIT BIT(7)
#define BINARY_BIT BIT(2)

typedef struct {
  uint8_t hours;
  uint8_t minutes;
  uint8_t seconds;
} rtc_time;


int (rtc_subscribe_int)(uint8_t *bit_no);

int (rtc_unsubscribe_int)();

int (read_time_register(uint8_t reg, uint8_t* output));

int (rtc_is_blocked)();

int (rtc_is_binary)();

int (rtc_read_time)(rtc_time *time);

void (rtc_update_time)(rtc_time *time);

int(rtc_to_binary)();

uint8_t (convert_bcd_to_decimal)(uint8_t *bcd);


#endif
