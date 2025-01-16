void calculate_score_array_to_roll_counts(const int arr[6], int counts[7]) {
  for (int i = 0; i < 7; i++) {
    counts[i] = 0;
  }

  for (int i = 0; i < 6; i++) {
    if (arr[i] >= 1 && arr[i] <= 6) {
      counts[arr[i]]++;
    }
  }
}

int calculate_score_of_a_kind(const int counts[7], int target) {
  for (int i = 1; i <= 6; i++) {
    if (counts[i] == target) {
      return i;
    }
  }
  return -1;
}

int calculate_score(const int arr[6]) {
  int counts[7];
  calculate_score_array_to_roll_counts(arr, counts);
  int sum = 0;

  // Check for six of a kind
  int six_of_a_kind = calculate_score_of_a_kind(counts, 6);
  if (six_of_a_kind != -1) {
    return 3000;
  }

  // Check for two triplets
  int triplet_count = 0;
  for (int i = 1; i <= 6; i++) {
    if (counts[i] == 3) {
      triplet_count++;
    }
  }
  if (triplet_count == 2) {
    return 2500;
  }

  // Check for four of a kind and a pair
  int four_of_a_kind = calculate_score_of_a_kind(counts, 4);
  int two_of_a_kind = calculate_score_of_a_kind(counts, 2);
  if (four_of_a_kind != -1 && two_of_a_kind != -1) {
    return 1500;
  }

  // Check for three pairs
  int pair_count = 0;
  for (int i = 1; i <= 6; i++) {
    if (counts[i] == 2) {
      pair_count++;
    }
  }
  if (pair_count == 3) {
    return 1500;
  }

  // Check for straight (1-6 all present)
  if (counts[1] == 1 && counts[2] == 1 && counts[3] == 1 &&
      counts[4] == 1 && counts[5] == 1 && counts[6] == 1) {
    return 1500;
  }

  // Check for five of a kind
  int five_of_a_kind = calculate_score_of_a_kind(counts, 5);
  if (five_of_a_kind != -1) {
    sum = 2000;
    counts[five_of_a_kind] = 0;
  }

  // Check for four of a kind
  if (four_of_a_kind != -1) {
    sum = 1000;
    counts[four_of_a_kind] = 0;
  }

  // Check for three of a kind
  int three_of_a_kind = calculate_score_of_a_kind(counts, 3);
  if (three_of_a_kind != -1) {
    if (three_of_a_kind == 1) {
      sum = sum + 300;
    } else {
      sum = sum + three_of_a_kind * 100;
    }

    counts[three_of_a_kind] = 0;
  }

  // Points for ones and fives
  sum = sum + counts[1] * 100;
  counts[1] = 0;

  sum = sum + counts[5] * 50;
  counts[5] = 0;

  return sum;
}
