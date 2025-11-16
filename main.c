#include "stdio.h"
#include <stdint.h>

#define arraylist(a) typedef struct { \
    a contents; \
    int size; \
} name;

arraylist(int);

int main() {
    return 0;
}