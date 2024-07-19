#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_string(char *string);

typedef unsigned int uint; 

int main(void)
{
    uint n;

    printf("Please Enter a number: ");
    scanf("%d", &n);

    char *forward = malloc((n - 1) * sizeof(char));
    init_string(forward);

    char *reverse = malloc((n - 1) * sizeof(char)); 
    init_string(reverse);
    
    char *strings[n - 1];

    printf("*");

    for (uint i=1;i<=n;i++)
    {
        char *reverse_print = reverse + (n - i);
    
        printf("%s%d%s*", forward, i, reverse_print);

        forward[i-1] = (char) i + 48;
        
        if (i != n)
        {
            reverse[n-i-1] = (char) i + 48;
            
            char *tmp = malloc((i*2-1) * sizeof(char));

            strcpy(tmp, forward);
            strcat(tmp, reverse + (n - i));

            strings[n-1-i] = tmp;
            
            free(tmp);
        }
    }

    for (uint i=0;i<n-1;i++)
    {
        printf("%s*", strings[i]);
    }

    free(forward);
    free(reverse);

    printf("\n");
}


void init_string(char *string)
{
    uint len = strlen(string);

    for (uint i = 0; i < len; i++)
    {
        string[i] = '\0';
    }
}