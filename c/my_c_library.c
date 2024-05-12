#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


int string_to_int(char* string);
int len(char* string);
void print_array(int size,int array[]);
int* swap_numbers(int num1, int num2);
int* selection_sort(int numbers[], int len);
int* buuble_sort(int numbers[], int len);


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

int* swap_numbers(int num1, int num2)
{
    int *nums = (int*) malloc(2 * sizeof(int));
    num1 = num1 ^ num2;
    num2 = num1 ^ num2;
    num1 = num1 ^ num2;
    nums[0] = num1;
    nums[1] = num2;
    return nums;
}

int* selection_sort(int numbers[], int len){
    int min, i,j;
    for(i=0;i<len-1;i++)
    {
        min = i;
        for(j=i+1;j<len;j++)
        {
            if(numbers[j]<=numbers[min])
            {
                min = j;
            }
        }
        if (min != i){
            numbers[min] = numbers[i] ^ numbers[min];
            numbers[i] = numbers[i] ^ numbers[min];
            numbers[min] = numbers[i] ^ numbers[min];
        }
    }
    return numbers;
}

int* buuble_sort(int numbers[], int len)
{
    int i;
    bool check = true;
    while(check)
    {
        check =false;
        for(i=0;i<len-1;i++)
        {
            if(numbers[i]>numbers[i+1])
            {
                check = true;
                numbers[i] = numbers[i] ^ numbers[i+1];
                numbers[i+1] = numbers[i] ^ numbers[i+1];
                numbers[i] = numbers[i] ^ numbers[i+1];
            }
        }
    }
}