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
for(int i = 0; i < 4; i++) {
    switch(i) {
      case 0:
        play[i] = create_sprite(p_xpm);
        break;
      case 1:
        play[i] = create_sprite(l_xpm);
        break;
      case 2:
        play[i] = create_sprite(a_xpm);
        break;
      case 3:
        play[i] = create_sprite(y_xpm);
        break;
    }
  }
}

void createQuit(){
  for(int i = 0; i < 4; i++) {
    switch(i) {
      case 0:
        quit[i] = create_sprite(q_xpm);
        break;
      case 1:
        quit[i] = create_sprite(u_xpm);
        break;
      case 2:
        quit[i] = create_sprite(i_xpm);
        break;
      case 3:
        quit[i] = create_sprite(t_xpm);
        break;
    }
  }
}
