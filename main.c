#include <stdio.h>
#include "stdarg.h"

int total(int num, ...){
    va_list args;
    va_start(args, num);

    int total = 0;
    for (int i = 0; i < num; ++i) {
        total += va_arg(args, int);
    }
    va_end(args);
    return total;
}

int main() {
    // statements();
    printf("The total is: %d", total(2, 4, 6));
}
