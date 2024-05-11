#include <stdio.h>

typedef struct my{
    int num;
    int two;
}my;

typedef char* string;

int main(void)
{
    string a = "asd";
    printf("%s\n", a);
    my m;
    printf("%p\n", &m);
    printf("%p\n", &m.num);
    printf("%p\n", &m.two);
}