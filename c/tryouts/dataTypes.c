#include <stdio.h>

int num;

void main(){
    printf("%d\n", num);
    int number;
    number = 10;

    int* number_adr = &number;
    printf("Value: %d, address:%p.\n", *number_adr, number_adr);

    number = number + 60;
    int new_number = number + 60;
    printf("Value: %d, address:%p.\n", number, number_adr);
    printf("Value: %d, address:%p.\n", new_number, &new_number);

    char c = (char) number;
    printf("Variable 'number' ascii value is: %c.\n", c);
    

    char ch = 'A' + 1;
    printf("%c\n", ch);
    int ch_ascii = (int) ch + 1;
    char ch_next = (char) ch_ascii;
    printf("%c\n", ch_next);
}