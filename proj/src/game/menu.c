#include "menu.h"

int currentOption = 0;

int getCurrentOption() {
  return currentOption;
}

void setCurrentOption(int option) {
  currentOption = option;
}

void increaseCurrentOption() {
  if (currentOption == 2) {
    currentOption = 0;
  }
  else {
    currentOption++;
  }
}

void decreaseCurrentOption() {
  if (currentOption == 0) {
    currentOption = 2;
  }
  else {
    currentOption--;
  }
}

void createPlay() {
  play = create_sprite(play_xpm);
}

void createQuit(){
  quit = create_sprite(quit_xpm);
}

int readTime() {
  if( rtc_read_time(&timeRTC) != 0) {
    printf("Error in rtc_read_time inside: %s\n", __func__);
    return EXIT_FAILURE;
  }

  int tempHours = timeRTC.hours;
  int tempMinutes = timeRTC.minutes;

  for(int i = 0; i < 2; i++) {
    uint8_t digit = tempHours % 10;
    tempHours /= 10;
    hours[i] = numbers[digit];
  }
  for(int i = 0; i < 2; i++) {
    uint8_t digit = tempMinutes % 10;
    tempMinutes /= 10;
    minutes[i] = numbers[digit];
  }
  dots = create_sprite(dots_xpm);
  return EXIT_SUCCESS;
}
