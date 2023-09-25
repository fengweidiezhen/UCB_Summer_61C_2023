#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "asserts.h"
// Necessary due to static functions in state.c
#include "state.c"

/* Look at asserts.c for some helpful assert functions */

int greater_than_forty_two(int x) {
  return x > 42;
}

bool is_vowel(char c) {
  char* vowels = "aeiouAEIOU";
  for (int i = 0; i < strlen(vowels); i++) {
    if (c == vowels[i]) {
      return true;
    }
  }
  return false;
}

/*
  Example 1: Returns true if all test cases pass. False otherwise.
    The function greater_than_forty_two(int x) will return true if x > 42. False otherwise.
    Note: This test is NOT comprehensive
*/
bool test_greater_than_forty_two() {
  int testcase_1 = 42;
  bool output_1 = greater_than_forty_two(testcase_1);
  if (!assert_false("output_1", output_1)) {
    return false;
  }

  int testcase_2 = -42;
  bool output_2 = greater_than_forty_two(testcase_2);
  if (!assert_false("output_2", output_2)) {
    return false;
  }

  int testcase_3 = 4242;
  bool output_3 = greater_than_forty_two(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  return true;
}

/*
  Example 2: Returns true if all test cases pass. False otherwise.
    The function is_vowel(char c) will return true if c is a vowel (i.e. c is a,e,i,o,u)
    and returns false otherwise
    Note: This test is NOT comprehensive
*/
bool test_is_vowel() {
  char testcase_1 = 'a';
  bool output_1 = is_vowel(testcase_1);
  if (!assert_true("output_1", output_1)) {
    return false;
  }

  char testcase_2 = 'e';
  bool output_2 = is_vowel(testcase_2);
  if (!assert_true("output_2", output_2)) {
    return false;
  }

  char testcase_3 = 'i';
  bool output_3 = is_vowel(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  char testcase_4 = 'o';
  bool output_4 = is_vowel(testcase_4);
  if (!assert_true("output_4", output_4)) {
    return false;
  }

  char testcase_5 = 'u';
  bool output_5 = is_vowel(testcase_5);
  if (!assert_true("output_5", output_5)) {
    return false;
  }

  char testcase_6 = 'k';
  bool output_6 = is_vowel(testcase_6);
  if (!assert_false("output_6", output_6)) {
    return false;
  }

  return true;
}

/* Task 4.1 */

bool is_tail(char c) {
  return c == '^' || c == '<' || c == 'v' || c == '>';
}

bool test_is_tail() {
  char testcase_1 = '^';
  bool output_1 = is_tail(testcase_1);
  if (!assert_true("output_1", output_1)) {
    return false;
  }

  char testcase_2 = '<';
  bool output_2 = is_tail(testcase_2);
  if (!assert_true("output_2", output_2)) {
    return false;
  }

  char testcase_3 = 'v';
  bool output_3 = is_tail(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  char testcase_4 = '>';
  bool output_4 = is_tail(testcase_4);
  if (!assert_true("output_4", output_4)) {
    return false;
  }

  char testcase_5 = 'x';
  bool output_5 = is_tail(testcase_5);
  if (!assert_false("output_5", output_5)) {
    return false;
  }

  return true;
}

bool is_head(char c) {
  return c == 'A' || c == 'a' || c == 'E' || c == 'e' || c == 'I' || c == 'i' ||
         c == 'O' || c == 'o' || c == 'U' || c == 'u';
}

bool test_is_head() {
  char testcase_1 = 'A';
  bool output_1 = is_head(testcase_1);
  if (!assert_true("output_1", output_1)) {
    return false;
  }

  char testcase_2 = 'e';
  bool output_2 = is_head(testcase_2);
  if (!assert_true("output_2", output_2)) {
    return false;
  }

  char testcase_3 = 'I';
  bool output_3 = is_head(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  char testcase_4 = 'o';
  bool output_4 = is_head(testcase_4);
  if (!assert_true("output_4", output_4)) {
    return false;
  }

  char testcase_5 = 'U';
  bool output_5 = is_head(testcase_5);
  if (!assert_true("output_5", output_5)) {
    return false;
  }

  char testcase_6 = 'x';
  bool output_6 = is_head(testcase_6);
  if (!assert_false("output_6", output_6)) {
    return false;
  }

  return true;
}

bool is_snake(char c) {
  return is_head(c) || is_tail(c);
}

bool test_is_snake() {
  char testcase_1 = '^';
  bool output_1 = is_snake(testcase_1);
  if (!assert_true("output_1", output_1)) {
    return false;
  }

  char testcase_2 = 'e';
  bool output_2 = is_snake(testcase_2);
  if (!assert_true("output_2", output_2)) {
    return false;
  }

  char testcase_3 = 'I';
  bool output_3 = is_snake(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  char testcase_4 = 'o';
  bool output_4 = is_snake(testcase_4);
  if (!assert_true("output_4", output_4)) {
    return false;
  }

  char testcase_5 = 'U';
  bool output_5 = is_snake(testcase_5);
  if (!assert_true("output_5", output_5)) {
    return false;
  }

  char testcase_6 = 'x';
  bool output_6 = is_snake(testcase_6);
  if (!assert_false("output_6", output_6)) {
    return false;
  }

  return true;
}

char body_to_tail(char c) {
  switch (c) {
    case 'v':
      return '^';
    case '>':
      return '<';
    case '^':
      return 'v';
    case '<':
      return '>';
    default:
      return c;
  }
}

bool test_body_to_tail() {
  char testcase_1 = 'v';
  char output_1 = body_to_tail(testcase_1);
  if (!assert_equal_char("output_1", output_1, '^')) {
    return false;
  }

  char testcase_2 = '>';
  char output_2 = body_to_tail(testcase_2);
  if (!assert_equal_char("output_2", output_2, '<')) {
    return false;
  }

  char testcase_3 = '^';
  char output_3 = body_to_tail(testcase_3);
  if (!assert_equal_char("output_3", output_3, 'v')) {
    return false;
  }

  char testcase_4 = '<';
  char output_4 = body_to_tail(testcase_4);
  if (!assert_equal_char("output_4", output_4, '>')) {
    return false;
  }

  char testcase_5 = 'x';
  char output_5 = body_to_tail(testcase_5);
  if (!assert_equal_char("output_5", output_5, 'x')) {
    return false;
  }

  return true;
}

char head_to_body(char c) {
  switch (c) {
    case 'A':
      return 'a';
    case 'a':
      return 'A';
    case 'E':
      return 'e';
    case 'e':
      return 'E';
    case 'I':
      return 'i';
    case 'i':
      return 'I';
    case 'O':
      return 'o';
    case 'o':
      return 'O';
    case 'U':
      return 'u';
    case 'u':
      return 'U';
    default:
      return c;
  }
}

bool test_head_to_body() {
  char testcase_1 = 'A';
  char output_1 = head_to_body(testcase_1);
  if (!assert_equal_char("output_1", output_1, 'a')) {
    return false;
  }

  char testcase_2 = 'e';
  char output_2 = head_to_body(testcase_2);
  if (!assert_equal_char("output_2", output_2, 'E')) {
    return false;
  }

  char testcase_3 = 'I';
  char output_3 = head_to_body(testcase_3);
  if (!assert_equal_char("output_3", output_3, 'i')) {
    return false;
  }

  char testcase_4 = 'o';
  char output_4 = head_to_body(testcase_4);
  if (!assert_equal_char("output_4", output_4, 'O')) {
    return false;
  }

  char testcase_5 = 'U';
  char output_5 = head_to_body(testcase_5);
  if (!assert_equal_char("output_5", output_5, 'u')) {
    return false;
  }

  char testcase_6 = 'x';
  char output_6 = head_to_body(testcase_6);
  if (!assert_equal_char("output_6", output_6, 'x')) {
    return false;
  }

  return true;
}

/* Task 4.2 */

int add_one(int x) {
  return x + 1;
}

bool test_add_one() {
  int testcase_1 = 0;
  int output_1 = add_one(testcase_1);
  if (!assert_equal_int("output_1", output_1, 1)) {
    return false;
  }

  int testcase_2 = 10;
  int output_2 = add_one(testcase_2);
  if (!assert_equal_int("output_2", output_2, 11)) {
    return false;
  }

  int testcase_3 = -5;
  int output_3 = add_one(testcase_3);
  if (!assert_equal_int("output_3", output_3, -4)) {
    return false;
  }

  return true;
}

int multiply_by_two(int x) {
  return x * 2;
}

bool test_multiply_by_two() {
  int testcase_1 = 2;
  int output_1 = multiply_by_two(testcase_1);
  if (!assert_equal_int("output_1", output_1, 4)) {
    return false;
  }

  int testcase_2 = 5;
  int output_2 = multiply_by_two(testcase_2);
  if (!assert_equal_int("output_2", output_2, 10)) {
    return false;
  }

  int testcase_3 = -3;
  int output_3 = multiply_by_two(testcase_3);
  if (!assert_equal_int("output_3", output_3, -6)) {
    return false;
  }

  return true;
}

int subtract_three(int x) {
  return x - 3;
}

bool test_subtract_three() {
  int testcase_1 = 10;
  int output_1 = subtract_three(testcase_1);
  if (!assert_equal_int("output_1", output_1, 7)) {
    return false;
  }

  int testcase_2 = 0;
  int output_2 = subtract_three(testcase_2);
  if (!assert_equal_int("output_2", output_2, -3)) {
    return false;
  }

  int testcase_3 = 7;
  int output_3 = subtract_three(testcase_3);
  if (!assert_equal_int("output_3", output_3, 4)) {
    return false;
  }

  return true;
}

int perform_operations(int x, int (*operations[])(int)) {
  for (int i = 0; i < 3; i++) {
    x = operations[i](x);
  }
  return x;
}

bool test_perform_operations() {
  int testcase_1 = 2;
  int (*operations_1[])(int) = {add_one, multiply_by_two, subtract_three};
  int output_1 = perform_operations(testcase_1, operations_1);
  if (!assert_equal_int("output_1", output_1, 3)) {
    return false;
  }

  int testcase_2 = 5;
  int (*operations_2[])(int) = {multiply_by_two, subtract_three, add_one};
  int output_2 = perform_operations(testcase_2, operations_2);
  if (!assert_equal_int("output_2", output_2, 8)) {
    return false;
  }

  int testcase_3 = 10;
  int (*operations_3[])(int) = {subtract_three, add_one, multiply_by_two};
  int output_3 = perform_operations(testcase_3, operations_3);
  if (!assert_equal_int("output_3", output_3, 17)) {
    return false;
  }

  return true;
}

/* Task 4.3 */

void print_array(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

void sort_array(int arr[], int size) {
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

bool test_sort_array() {
  int testcase_1[] = {5, 2, 7, 1, 9};
  int size_1 = sizeof(testcase_1) / sizeof(testcase_1[0]);
  sort_array(testcase_1, size_1);
  int expected_1[] = {1, 2, 5, 7, 9};
  if (!assert_equal_array("testcase_1", testcase_1, expected_1, size_1)) {
    return false;
  }

  int testcase_2[] = {10, 5, 3, 8, 2};
  int size_2 = sizeof(testcase_2) / sizeof(testcase_2[0]);
  sort_array(testcase_2, size_2);
  int expected_2[] = {2, 3, 5, 8, 10};
  if (!assert_equal_array("testcase_2", testcase_2, expected_2, size_2)) {
    return false;
  }

  int testcase_3[] = {4, 9, 1, 6, 3};
  int size_3 = sizeof(testcase_3) / sizeof(testcase_3[0]);
  sort_array(testcase_3, size_3);
  int expected_3[] = {1, 3, 4, 6, 9};
  if (!assert_equal_array("testcase_3", testcase_3, expected_3, size_3)) {
    return false;
  }

  return true;
}

int main() {
  bool result = true;
  result &= test_is_tail();
  result &= test_is_head();
  result &= test_is_snake();
  result &= test_body_to_tail();
  result &= test_head_to_body();
  result &= test_add_one();
  result &= test_multiply_by_two();
  result &= test_subtract_three();
  result &= test_perform_operations();
  result &= test_sort_array();

  if (result) {
    printf("All tests passed successfully!\n");
  } else {
    printf("Some tests failed!\n");
  }

  return 0;
}
