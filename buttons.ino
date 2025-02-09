void die_press(int number) {
  if (is_confirm_mode_bust == true || is_confirm_mode_bank == true) {
    return;
  }

  if (is_in_setup) {
    init_players(number);
  } else {
    for (int i = 0; i < 6; i++) {
      if (dice[i] == 0) {
        dice[i] = number;
        break;
      }
    }
    display_points_locked_in();
  }
}

void add_1() { die_press(1); }
void add_2() { die_press(2); }
void add_3() { die_press(3); }
void add_4() { die_press(4); }
void add_5() { die_press(5); }
void add_6() { die_press(6); }

void next_turn() {
  if (current_player == player_count - 1) {
    current_player = 0;
  } else {
    current_player++;
  }

  display_scores();
}

void enter_confirm_bust_mode() {
  is_confirm_mode_bust = true;
  digitalWrite(RED_LED_PIN, HIGH);
}

void leave_confirm_bust_mode() {
  is_confirm_mode_bust = false;
  digitalWrite(RED_LED_PIN, LOW);
}
void enter_confirm_bank_mode() {
  is_confirm_mode_bank = true;
  digitalWrite(GREEN_LED_PIN, HIGH);
}

void leave_confirm_bank_mode() {
  is_confirm_mode_bank = false;
  digitalWrite(GREEN_LED_PIN, LOW);
}

void clear() {
  if (is_confirm_mode_bust == true) {
    leave_confirm_bust_mode();
    return;
  }

  if (is_confirm_mode_bank == true) {
    leave_confirm_bank_mode();
    return;
  }

  for (int i = 0; i < 6; i++) {
    dice[i] = 0;
  }
  display_points_locked_in();
}

void bust() {
  if (is_confirm_mode_bank == true) { return; }

  if (is_confirm_mode_bust == true) {
    leave_confirm_bust_mode();
    points_locked_in = 0;
    clear();
    next_turn();
  } else {
    enter_confirm_bust_mode();
  }
}

void lock() {
  if (is_confirm_mode_bust == true) { return; }
  if (is_confirm_mode_bank == true) { return; }

  points_locked_in = points_locked_in + calculate_score(dice);
  clear();
}

void bank() {
  if (is_confirm_mode_bust == true) { return; }

  if (is_confirm_mode_bank == true) {
    leave_confirm_bank_mode();
    lock();
    player_scores[current_player] = player_scores[current_player] + points_locked_in;
    points_locked_in = 0;
    clear();
    next_turn();
  } else {
    enter_confirm_bank_mode();
  }
}
