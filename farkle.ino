#include <EasyButton.h>
#include <TM1637TinyDisplay6.h>
#include <TM1637TinyDisplay.h>

#define BUTTON_PIN_1 1
#define BUTTON_PIN_2 2
#define BUTTON_PIN_3 3
#define BUTTON_PIN_4 4
#define BUTTON_PIN_5 5
#define BUTTON_PIN_6 6
#define BUTTON_PIN_LOCK 7
#define BUTTON_PIN_BANK 8

EasyButton button_1(BUTTON_PIN_1);
EasyButton button_2(BUTTON_PIN_2);
EasyButton button_3(BUTTON_PIN_3);
EasyButton button_4(BUTTON_PIN_4);
EasyButton button_5(BUTTON_PIN_5);
EasyButton button_6(BUTTON_PIN_6);
EasyButton button_lock(BUTTON_PIN_LOCK);
EasyButton button_bank(BUTTON_PIN_BANK);

TM1637TinyDisplay6 score_display(11, 12);
TM1637TinyDisplay locked_in_display(9, 10);

int score = 0;
int points_locked_in = 0;
int dice[6] = { 0, 0, 0, 0, 0, 0 };

void add_1() {
  add_die(1);
}

void add_2() {
  add_die(2);
}

void add_3() {
  add_die(3);
}

void add_4() {
  add_die(4);
}

void add_5() {
  add_die(5);
}

void add_6() {
  add_die(6);
}

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

void bust() {
  clear();
  points_locked_in = 0;
}

void lock() {
  points_locked_in = points_locked_in + calculate_score(dice);
  clear();
}

void bank() {
  lock();
  score = score + points_locked_in;
  points_locked_in = 0;
}

void setup() {
  button_1.begin();
  button_1.onPressed(add_1);
  button_2.begin();
  button_2.onPressed(add_2);
  button_3.begin();
  button_3.onPressed(add_3);
  button_4.begin();
  button_4.onPressed(add_4);
  button_5.begin();
  button_5.onPressed(add_5);
  button_6.begin();
  button_6.onPressed(add_6);
  button_lock.begin();
  button_lock.onPressed(lock);
  button_bank.begin();
  button_bank.onPressed(bank);

  locked_in_display.begin();
  locked_in_display.setBrightness(0);

  score_display.begin();
  score_display.setBrightness(0);
}

void loop() {
  button_1.read();
  button_2.read();
  button_3.read();
  button_4.read();
  button_5.read();
  button_6.read();
  button_lock.read();
  button_bank.read();

  score_display.showNumber(score);
  locked_in_display.showNumber(points_locked_in);
}
