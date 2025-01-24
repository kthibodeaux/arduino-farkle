#include <Wire.h>
#include <PCF8575.h>

PCF8575 score_display(0x21);
int score = 0;
int temp_score = 0;
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

void lock() {
  temp_score = temp_score + calculate_score(dice);
  clear();
}

void bank() {
  lock();
  score = score + temp_score;
  temp_score = 0;
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
  lock(); // 650
  add_die(1);
  lock(); // 100
  add_die(3);
  add_die(3);
  add_die(3);
  add_die(3);
  add_die(3);
  add_die(3);
  bank(); // 3000
}

void loop() {
  display_score(score);
}
