#include <Wire.h>
#include <PCF8575.h>

PCF8575 score_display(0x21);
int score = 0;
int dice[6] = { 0, 0, 0, 0, 0, 0 };

void add_die(int number) {
  for (int i = 0; i < 6; i++) {
    if (dice[i] == 0) {
      dice[i] = number;
      break;
    }
  }
}

void remove_die() {
  for (int i = 5; i >= 0; i--) {
    if (dice[i] != 0) {
      dice[i] = 0;
      break;
    }
  }
}

void clear() {
  for (int i = 0; i < 6; i++) {
    dice[i] = 0;
  }
}

void bank() {
  score = score + calculate_score(dice);
}

void setup() {
  Wire.begin();

  display_score_setup();

  add_die(6);
  add_die(6);
  add_die(6);
  add_die(6);
  remove_die();
  add_die(5);

  bank();
}

void loop() {
  display_score(score);
}
