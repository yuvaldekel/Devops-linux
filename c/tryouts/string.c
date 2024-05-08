#include <stdio.h> 
#include <stdlib.h>

int main(int argc, char* argv[])
{
    char *s = "445";
    char *s1 = s +1;    
    char c =  *s1;
    printf("%s\n", s);
    printf("%s\n", s1);
    printf("%c\n", c);


    char string[] = "BYE!";
    char string2[5] = "bye";
    string2[3] = '!';
    string2[4] = '!';

    printf("%s\n", string2);    
    printf("%p\n", &string);    
    printf("%p\n", &string2);    

}