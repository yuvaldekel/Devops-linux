#include <stdio.h> 
#include <stdbool.h> 

int len(char* string);
int string_to_int(char* string);

int main(int argc, char* argv[])
{
    printf("argc = %d\n", argc);    
    
    char* string = argv[1];
    printf("%p\n", string);
    printf("%p\n", argv[1]);
    
    int number_arg = string_to_int(argv[1]);
    printf("argv[1] = %d\n", number_arg);

}

int len(char* string)
{
    int i = 0;
    while (string[i] != '\0'){
        char c = string[i];
        i++;
    }
    return i;
}

int string_to_int(char* string)
{
    int number = 0;
    
    int length = len(string);
    int i = 0;

    for(i=0;i<length;i++){
        int digit = string[i] - '0';
        number = number * 10 + digit;
    }
 
    return number;
}