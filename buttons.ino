void die_press(int number) {
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

void clear() {
  for (int i = 0; i < 6; i++) {
    dice[i] = 0;
  }
  display_points_locked_in();
}

void bust() {
  points_locked_in = 0;
  clear();
  next_turn();
}

void lock() {
  points_locked_in = points_locked_in + calculate_score(dice);
  clear();
}

void bank() {
  lock();
  player_scores[current_player] = player_scores[current_player] + points_locked_in;
  points_locked_in = 0;
  clear();
  next_turn();
}
