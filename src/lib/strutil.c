#ifndef STRUTIL_C
#define STRUTIL_C

#include <stdbool.h>

bool is_whitespace(char c) { return c == ' ' || c == '\n'; }

bool is_numeric(int c) {
  int lowest_num = '0';
  int highest_num = '9';
  return c >= lowest_num && c <= highest_num;
}

bool is_alphabetic(int c) {
  int lowest_char1 = 'A';
  int highest_char1 = 'Z';
  int lowest_char2 = 'a';
  int highest_char2 = 'z';
  return (c >= lowest_char1 && c <= highest_char1) ||
         (c >= lowest_char2 && c <= highest_char2);
}

#endif