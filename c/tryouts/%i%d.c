#include <stdio.h>
 
int main()
{
    int a, b, c;
    int num = 0x12;

    printf("Enter value of a in decimal format: ");
    scanf("%d", &a);
 
    printf("Enter value of b in octal format: ");
    scanf("%i", &b);
 
    printf("Enter value of c in hexadecimal format: ");
    scanf("%i", &c);
 
    printf("a = %i, b = %i, c = %i\n", a, b, c);
 
    printf("%d\n", num);
 
    return 0;
}
