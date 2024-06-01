#include "wait_menu.h"

void draw_wait_menu(bool isDay) {
  if (isDay) {
    draw_background(dayDesert->map);
  }
  else {
    draw_background(nightDesert->map);
  }
  vg_page_flipping();
}
