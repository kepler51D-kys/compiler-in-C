#ifndef TOKENIZER_C
#define TOKENIZER_C

#define TOKENIZER_MAX_NUMBER_LEN 16
#define TOKENIZER_MAX_IDENTIFIER_LEN 256

#include <lib/arrlist.c>
#include <lib/strutil.c>
#include <stdio.h>
#include <stdlib.h>

typedef enum Token {
  token_eof,
  token_binary_operation,
  token_rbracket,
  token_lbracket,
  token_rcurly_bracket,
  token_lcurly_bracket,
  token_semicolon,
  token_comma,
  token_identifier,
  token_integer,
  token_unknown,
} Token;

typedef struct TokenElem {
  Token token;
  union {
    int int_value;
    char *str_value;
    char char_value;
  } value;
} TokenElem;

DEFINE_ARRAYLIST(TokenElem, TokenList);

TokenElem get_next_token(int (*reader)()) {
  TokenElem ret;
  int c;
  do {
    c = reader();
  } while (c != EOF && is_whitespace(c));
  if (c == EOF) {
    ret.token = token_eof;
  } else if (is_numeric(c)) {
    char number_str[TOKENIZER_MAX_NUMBER_LEN + 1];
    int i;
    for (i = 0; i < TOKENIZER_MAX_NUMBER_LEN && is_numeric(c); i++) {
      number_str[i] = c;
      c = reader();
    }
    number_str[i] = '\0';
    char *endptr;
    int x = (int)strtol(number_str, &endptr, 10);
    ret.value.int_value = x;
    ret.token = token_integer;
  } else if (is_alphabetic(c)) {
    char *identifier_str =
        malloc((TOKENIZER_MAX_IDENTIFIER_LEN + 1) * sizeof(char));
    int i;
    for (i = 0; i < TOKENIZER_MAX_IDENTIFIER_LEN &&
                (is_numeric(c) || is_alphabetic(c));
         i++) {
      identifier_str[i] = c;
      c = reader();
    }
    identifier_str[i] = '\0';
    ret.value.str_value = identifier_str;
    ret.token = token_identifier;
  } else {
    switch (c) {
    case '{':
      ret.token = token_lcurly_bracket;
      break;
    case '}':
      ret.token = token_rcurly_bracket;
      break;
    case '(':
      ret.token = token_lbracket;
      break;
    case ')':
      ret.token = token_rbracket;
      break;
    case ',':
      ret.token = token_comma;
      break;
    case ';':
      ret.token = token_semicolon;
    default:
      ret.token = token_binary_operation;
      ret.value.char_value = c;
      break;
    }
  }
  return ret;
}

TokenList *tokenize(int (*reader)()) {
  TokenList *list = TokenList_init();
  TokenElem current_elem;
  do {
    current_elem = get_next_token(reader);
    TokenList_append(list, current_elem);
  } while (current_elem.token != token_eof);
  return list;
}

#endif // TOKENIZER_C