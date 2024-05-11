#include <cs50.h>
#include <stdio.h>
#include <string.h>

int N = 2;

typedef char* string;

typedef struct Person
{
    string name;
    string number;
}person;

int main(void)
{
    int i;
    person phonebook[N];

    for(i=0;i<N;i++)
    {
        phonebook[i].name = get_string("Enter name: "); 
        phonebook[i].number = get_string("Enter number: ");
    }

    string name = get_string("Enter the name that you want to search: ");
    
    for(i=0;i<N;i++)
    {
        if (strcmp(name, phonebook[i].name) == 0)
        {
            printf("Found, %s's number is %s\n", phonebook[i].name, phonebook[i].number);
            return 0;
        }
    }
    
    printf("Did not found.\n");
    return 1;
}