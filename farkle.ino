#include <EasyButton.h>
#include "I2C_LCD.h"

#define BUTTON_PIN_1 9
#define BUTTON_PIN_2 8
#define BUTTON_PIN_3 7
#define BUTTON_PIN_4 6
#define BUTTON_PIN_5 5
#define BUTTON_PIN_6 4
#define BUTTON_PIN_BUST 14
#define BUTTON_PIN_CLEAR 15
#define BUTTON_PIN_LOCK 16
#define BUTTON_PIN_BANK 10
#define RED_LED_PIN 20
#define GREEN_LED_PIN 19

EasyButton button_1(BUTTON_PIN_1);
EasyButton button_2(BUTTON_PIN_2);
EasyButton button_3(BUTTON_PIN_3);
EasyButton button_4(BUTTON_PIN_4);
EasyButton button_5(BUTTON_PIN_5);
EasyButton button_6(BUTTON_PIN_6);
EasyButton button_bust(BUTTON_PIN_BUST);
EasyButton button_clear(BUTTON_PIN_CLEAR);
EasyButton button_lock(BUTTON_PIN_LOCK);
EasyButton button_bank(BUTTON_PIN_BANK);

I2C_LCD lcd(39);

int current_player = 0;
int player_count = 0;
bool is_in_setup = true;
int points_locked_in = 0;
int dice[6] = { 0, 0, 0, 0, 0, 0 };
int player_scores[6] = { 0, 0, 0, 0, 0, 0 };

uint8_t dice_chars[6][8]
{
  { 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00 },
  { 0x00, 0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00 },
  { 0x00, 0x01, 0x00, 0x04, 0x00, 0x10, 0x00, 0x00 },
  { 0x00, 0x11, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00 },
  { 0x00, 0x11, 0x00, 0x04, 0x00, 0x11, 0x00, 0x00 },
  { 0x00, 0x11, 0x00, 0x11, 0x00, 0x11, 0x00, 0x00 }
};

void display_score(int x, int y, int player_index) {
  lcd.setCursor(x, y);

  if (current_player == player_index) {
    lcd.print(">");
  } else {
    lcd.print(" ");
  }

  lcd.print(player_index + 1);
  lcd.print(": ");
  lcd.print(player_scores[player_index]);
}

void display_scores() {
  display_score(0, 0, 0);

  if (player_count >= 2) {
    display_score(10, 0, 1);
  }

  if (player_count >= 3) {
    display_score(0, 1, 2);
  }

  if (player_count >= 4) {
    display_score(10, 1, 3);
  }

  if (player_count >= 5) {
    display_score(0, 2, 4);
  }

  if (player_count == 6) {
    display_score(10, 2, 5);
  }
}

void display_points_locked_in() {
  lcd.setCursor(0, 3);
  lcd.clearEOL();

  lcd.setCursor(1, 3);
  lcd.print(points_locked_in);

  lcd.setCursor(8, 3);

  for (int i = 0; i < 6; i++) {
    if (dice[i] > 0) {
      lcd.special(dice[i] - 1);
      lcd.print(" ");
    }
  }
}

void init_players(int count) {
  is_in_setup = false;
  player_count = count;
  lcd.clear();
  display_scores();
}

void setup() {
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

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
  button_bust.begin();
  button_bust.onPressed(bust);
  button_clear.begin();
  button_clear.onPressed(clear);
  button_lock.begin();
  button_lock.onPressed(lock);
  button_bank.begin();
  button_bank.onPressed(bank);

  Wire.begin();
  Wire.setClock(100000);

  lcd.begin(20, 4);

  for (int i = 0; i < 6; i++) {
    lcd.createChar(i, dice_chars[i]);
    delay(5);
  }

  lcd.clear();

  lcd.setBacklight(1);

  lcd.center(1, "How many players?");
}


void loop() {
  button_1.read();
  button_2.read();
  button_3.read();
  button_4.read();
  button_5.read();
  button_6.read();
  button_bust.read();
  button_clear.read();
  button_lock.read();
  button_bank.read();
}
