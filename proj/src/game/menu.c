#include "menu.h"

int currentOption = 0;

/**
 * GETTERS AND SETTERS OF MENU VARIABLES
*/

int (getCurrentOption)() {
  return currentOption;
}

void (setCurrentOption)(int option) {
  currentOption = option;
}

void (increaseCurrentOption)() {
  if (currentOption == 2) {
    currentOption = 0;
  }
  else {
    currentOption++;
  }
}

void (decreaseCurrentOption)() {
  if (currentOption == 0) {
    currentOption = 2;
  }
  else {
    currentOption--;
  }
}



/**
 * TIME FUNCTION
*/

int (readTime)() {
  if (rtc_read_time(&timeRTC) != 0) {
    printf("Error in rtc_read_time inside: %s\n", __func__);
    return EXIT_FAILURE;
  }

  int tempHours = timeRTC.hours;
  int tempMinutes = timeRTC.minutes;

  for (int i = 0; i < 2; i++) {
    uint8_t digit = tempHours % 10;
    tempHours /= 10;
    hours[i] = numbers[digit];
  }
  for (int i = 0; i < 2; i++) {
    uint8_t digit = tempMinutes % 10;
    tempMinutes /= 10;
    minutes[i] = numbers[digit];
  }
  dots = create_sprite(dots_xpm);
  return EXIT_SUCCESS;
}



/**
 * DRAW FUNCTIONS 
*/


void (draw_menu)() {

  int startX = MAX_X - 170;

  for (int i = 0; i < 2; i++) {
    draw_sprite(hours[i], startX, MAX_Y - 65);
    startX -= 50;
  }

  draw_sprite(dots, startX + 145, MAX_Y - 65);

  startX = MAX_X - 30;
  for (int i = 0; i < 2; i++) {
    draw_sprite(minutes[i], startX, MAX_Y - 65);
    startX -= 50;
  }

  draw_sprite(play, MAX_X / 2, 100);
  draw_sprite(quit, MAX_X / 2, 200);

  switch (getCurrentOption()) {
    case SINGLEPLAYER:
      vg_draw_rectangle(MAX_X / 2 - 120, 140, 240, 10, 0x000000);
      break;
    case QUIT:
      vg_draw_rectangle(MAX_X / 2 - 120, 240, 240, 10, 0x000000);
      break;
    default:
      break;
  }
}
