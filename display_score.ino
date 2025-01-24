// Segment bitmaps for numbers 0-9 (common cathode)
const uint8_t segmentMap[] = {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111  // 9
};

// Pins for digit selection (P8-P11 on the PCF8575)
const uint8_t digitPins[] = {8, 9, 10, 11};

void display_score_setup() {
  score_display.begin();               // Initialize PCF8575
  score_display.write16(0x0000);       // Start with all pins LOW

  for (uint8_t i = 0; i < 4; i++) {
    score_display.write(digitPins[i], HIGH);
  }
}

void display_score_digit(uint8_t digit, uint8_t value) {
  // Turn off all digits
  for (uint8_t i = 0; i < 4; i++) {
    score_display.write(digitPins[i], HIGH); // Deactivate all digits
  }

  // Write the segment values for the digit
  uint8_t segments = segmentMap[value];
  for (uint8_t i = 0; i < 7; i++) {
    score_display.write(i, (segments & (1 << i)) ? HIGH : LOW);
  }

  // Activate the selected digit
  score_display.write(digitPins[digit], LOW);

  delay(3); // Small delay for persistence of vision
}

void display_score(int score) {
  int digit1 = score / 10000;        // Get the leftmost digit
  int digit2 = (score / 1000) % 10; // Get the second digit
  int digit3 = (score / 100) % 10;  // Get the third digit
  int digit4 = (score / 10) % 10;   // Get the fourth digit
  int digit5 = score % 10;

  display_score_digit(0, digit2);
  display_score_digit(1, digit3);
  display_score_digit(2, digit4);
  display_score_digit(3, digit5);
}
