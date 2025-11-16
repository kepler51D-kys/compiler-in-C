#ifndef TOKENIZER_C
#define TOKENIZER_C

typedef enum Token {
  token_eof,
  token_binary_operation,
  token_rparen,
  token_lparen,
  token_identifier,
} Token;

#endif // TOKENIZER_C