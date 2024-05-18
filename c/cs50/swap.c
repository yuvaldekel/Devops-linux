#include <stdio.h>

void swap(int *a, int* b);

int main(int argc, char *argv)
{
    int a = 5;
    int b = 10;

    printf("Before a = %d, b = %d.\n", a, b);
    swap(&a, &b);
    printf("After a = %d, b = %d.\n", a, b);
}

void swap(int *a, int* b)
{
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}