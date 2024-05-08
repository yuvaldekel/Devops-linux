#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int string_to_int(char* string);
int len(char* string);
void print_array(int size,int array[]);

int main(int agrc, char *argv[])
{
    printf("This is Yuval's c library, calling it does noting.\n");
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

void print_array(int size,int array[])
{
    int i;
    printf("[");
    for (i=0;i<size;i++)
    {
        printf("%d", array[i]);
        if (i != size -1) 
            printf(",");
    }
    printf("]\n");
}