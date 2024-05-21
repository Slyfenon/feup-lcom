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
