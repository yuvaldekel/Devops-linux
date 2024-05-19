#include <stdio.h>

typedef struct my{
    int num;
    int two;
}my;

int main(void)
{
    my m = {1,2};
    int num1 = 5;
    int num2 = 1;
    int num3 = 3;
    int num4 = 3;
    char *st = "ff";

    


    printf("%p\n", &num1);
    printf("%p\n", &num2);
    printf("%p\n", &num3);
    printf("%p\n", &num4);
    printf("%p\n", &m);
    printf("%c\n", *st);
}