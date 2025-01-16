#include <Wire.h>
#include <PCF8575.h>

PCF8575 score_display(0x21);
int score = 0;

void setup() {
  Wire.begin();

  display_score_setup();
  bank();
}

void bank() {
  int dice[6] = {4, 4, 4, 4, 4, 5};
  score = score + calculate_score(dice);
}

void loop() {
  display_score(score);
}
