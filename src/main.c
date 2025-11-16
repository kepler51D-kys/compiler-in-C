#include <stdio.h>

int main(int argc, char** argv) {
    if(argc == 1) {
        printf("No input file provided.");
        return 0;
    } else if (argc != 2) {
        printf("Too many arguments.");
        return 0;
    }
    char* input_file = argv[1];
    FILE* f = fopen(input_file, "r");
    if(f == NULL) {
        printf("Failed to open file.");
        return 0;
    }
    int c;
    while((c = fgetc(f)) != EOF) {
        printf("%c", c);
    }
    fclose(f);
    return 0;
}