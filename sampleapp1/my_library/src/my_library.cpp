#include "my_library.h"

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

void leak() {
    int* ptr = new int;
}