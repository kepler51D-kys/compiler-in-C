#include <lexer/tokenizer.c>
#include <stdio.h>

FILE *f;

int reader() { return fgetc(f); }

int main(int argc, char **argv) {
  if (argc == 1) {
    printf("No input file provided.");
    return 0;
  } else if (argc != 2) {
    printf("Too many arguments.");
    return 0;
  }
  char *input_file = argv[1];
  f = fopen(input_file, "r");
  if (f == NULL) {
    printf("Failed to open file.");
    return 0;
  }
  TokenList *list = tokenize(&reader);
  for (int i = 0; i < list->len; i++) {
    printf("%d ", list->list[i].token);
  }
  fclose(f);
  return 0;
}