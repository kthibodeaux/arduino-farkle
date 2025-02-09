void add_1() {
  if (is_in_setup) {
    init_players(1);
  } else {
    add_die(1);
  }
}

void add_2() {
  if (is_in_setup) {
    init_players(2);
  } else {
    add_die(2);
  }
}

void add_3() {
  if (is_in_setup) {
    init_players(3);
  } else {
    add_die(3);
  }
}

void add_4() {
  if (is_in_setup) {
    init_players(4);
  } else {
    add_die(4);
  }
}

void add_5() {
  if (is_in_setup) {
    init_players(5);
  } else {
    add_die(5);
  }
}

void add_6() {
  if (is_in_setup) {
    init_players(6);
  } else {
    add_die(6);
  }
}

void add_die(int number) {
  for (int i = 0; i < 6; i++) {
    if (dice[i] == 0) {
      dice[i] = number;
      break;
    }
  }
  display_points_locked_in();
}

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
