#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <signal.h>


void progress_bar(int size, int step);
char *n_string(int size, char ch);
void signal_callback_handler(int signum);



int main(void)
{
    progress_bar(40, 3);
    printf("DONE\n");
}


void progress_bar(int size, int step)
{
    signal(SIGINT, signal_callback_handler);
    printf("\033[?25l");

    for(int i=0;i<=size;i++)
    {
        char *left = n_string(size - i, '.');
        char *passed = n_string(i, '#');

        int percent = ((float) i / size) * 100;
        
        printf("\033[22;42mPROGRESS [%d%%]\033[0m", percent);
        printf(" [%s%s]\r", passed, left);
        fflush(stdout);
        
        free(left);
        free(passed);

        if (i % step == 0 || i == size)
        {
            int r = (rand() % 10) * pow(10, 5) * 1.5; 
            usleep(r);
        }
    }

    char *spaces = n_string(size + 20, ' ');
    printf("%s\r", spaces);
    free(spaces);

    printf("\033[?25h");
}


char *n_string(int size, char ch){
    char *string = malloc((size + 1) * sizeof(char));

    for(int i=0;i<size;i++)
    {
        string[i] = ch;
    }

    string[size] = '\0';
    return string;
}


void signal_callback_handler(int signum){
    
    if (signum == 2)
    {
        printf("\033[?25h\r");
    }

   exit(signum);
}
