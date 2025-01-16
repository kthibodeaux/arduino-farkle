void array_to_roll_counts(const int arr[6], int counts[7]) {
  for (int i = 0; i < 7; i++) {
    counts[i] = 0;
  }

  for (int i = 0; i < 6; i++) {
    if (arr[i] >= 1 && arr[i] <= 6) {
      counts[arr[i]]++;
    }
  }
}

int of_a_kind(const int counts[7], int target) {
  for (int i = 1; i <= 6; i++) {
    if (counts[i] == target) {
      return i;
    }
  }
  return -1;
}

int calculate_score(const int arr[6]) {
  int counts[7];
  array_to_roll_counts(arr, counts);
  int sum = 0;

  // Check for six of a kind
  int six_of_a_kind = of_a_kind(counts, 6);
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
  int four_of_a_kind = of_a_kind(counts, 4);
  int two_of_a_kind = of_a_kind(counts, 2);
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
  int five_of_a_kind = of_a_kind(counts, 5);
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
  int three_of_a_kind = of_a_kind(counts, 3);
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

void run_test(const int dice[6], int score) {
  int actual_score = calculate_score(dice);
  if (actual_score != score) {
    Serial.print("Actual Score: ");
    Serial.println(actual_score);
    Serial.print("Expected Score: ");
    Serial.println(score);
  } else {
    Serial.println(".");
  }
}

void run_tests() {
  int test_case_1[6] = { 4, 4, 4, 4, 4, 4 };
  run_test(test_case_1, 3000);

  int test_case_2[6] = { 5, 5, 5, 5, 5, 5 };
  run_test(test_case_2, 3000);

  int test_case_3[6] = { 1, 1, 1, 1, 1, 5 };
  run_test(test_case_3, 2050);

  int test_case_4[6] = { 1, 1, 1, 1, 2, 5 };
  run_test(test_case_4, 1050);

  int test_case_5[6] = { 3, 3, 3, 5, 5, 5 };
  run_test(test_case_5, 2500);

  int test_case_6[6] = { 3, 3, 3, 3, 5, 5 };
  run_test(test_case_6, 1500);

  int test_case_7[6] = { 1, 1, 3, 3, 4, 4 };
  run_test(test_case_7, 1500);

  int test_case_8[6] = { 1, 2, 3, 4, 5, 6 };
  run_test(test_case_8, 1500);

  int test_case_9[6] = { 4, 4, 4, 4, 4, 5 };
  run_test(test_case_9, 2050);

  int test_case_10[6] = { 4, 4, 4, 4, 4 };
  run_test(test_case_10, 2000);

  int test_case_11[6] = { 5, 4, 4, 4, 4, 4 };
  run_test(test_case_11, 2050);

  int test_case_12[6] = { 1, 1, 1, 1, 1, 3 };
  run_test(test_case_12, 2000);

  int test_case_13[6] = { 1, 1, 1, 1, 3 };
  run_test(test_case_13, 1000);

  int test_case_14[6] = { 1, 1, 1, 1, 3, 5 };
  run_test(test_case_14, 1050);

  int test_case_15[6] = { 1, 1, 1, 3, 5 };
  run_test(test_case_15, 350);

  int test_case_16[6] = { 5, 5, 3, 5 };
  run_test(test_case_16, 500);

  int test_case_17[6] = { 3, 3, 3, 5 };
  run_test(test_case_17, 350);

  Serial.println("All tests finished.");
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Nothing to do in the loop for now
}
