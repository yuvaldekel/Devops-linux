#include <stdio.h>

typedef unsigned int uint;

int main() {
    int a, b, c;
    a = '1' - '0';
    b = 'a' - 'b';
    c = a + b;

    printf("%d\n", a);
    printf("%d\n", b);
    printf("%d\n", c);
}