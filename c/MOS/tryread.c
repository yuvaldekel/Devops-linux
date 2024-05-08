#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern int errno;

int main(void){    
    int sz;
    char* c = (char*) malloc(100*sizeof(char));
    //char c[100];   

    int fd = open("/home/yuval/Documents/yuval/Devops-linux/c/read.txt", O_RDONLY );
    
    if (fd == -1)
    {
        perror("Error opening file");
        return 1;
    }

    sz = read(fd, c, 12);

    if (sz != -1){
        c[sz] = '\0';
        printf("%s\n", c);
    }
    else
        perror("Error reading from file");
    
    close(fd);
}  