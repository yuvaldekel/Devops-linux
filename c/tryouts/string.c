#include <stdio.h> 
#include <stdlib.h>

int main(int argc, char* argv[])
{
    char s[] = "445";
    char *s1 = s +1;
    s1[0] = '5';
    char c =  *s1;
    printf("%s\n", s);
    printf("%s\n", s1);
    printf("c %c\n", c);

    char *str = malloc(4 * sizeof(char));
    str[0] = '1';
    str[1] = '2';
    str[2] = '3';
    str[3] = '4';
    printf("%s\n", str);    

    char string[] = "BYE!";
    char string2[5] = "bye";
    string2[3] = '!';
    string2[4] = '!';

    printf("%s\n", string2);    
    printf("%p\n", &string);    
    printf("%p\n", &string2);   

    char *string1;
    string1 = "sss";
    printf("%s\n", string1);    


}