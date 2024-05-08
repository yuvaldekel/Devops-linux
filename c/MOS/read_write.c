#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int string_to_int(char* string);
int len(char* string);

extern int errno;

int main(int argc, char* argv[]){
    
    if (argc != 3)
    {
        errno = 22;
        perror("");
        return errno;
    }

    int offset;
    char *w = argv[1];
    int file_size = string_to_int(argv[2]);
    
    int bytes_to_write = len(w);
    
    char* r = (char*) malloc((bytes_to_write + file_size) *sizeof(char));

    int fd = open("/home/yuval/Documents/yuval/Devops-linux/c/MOS/rdwr.txt", O_RDWR);
    if (fd == -1)
    {
        perror("Error opening file (line 14)");
        return errno;
    }

    offset = lseek(fd, 0, SEEK_END);
    if (offset == -1)
    {
        perror("Error moving pointer file (line 22)");
        return errno;
    }

    int writen = write(fd, w, bytes_to_write);
    if (writen == -1)
    {
        perror("Error wroting to the file (line 30)");
        return errno;
    }

    offset = lseek(fd, 0, SEEK_SET);
    if (offset == -1)
    {
        perror("Error moving pointer file (line 38)");
        return errno;
    }

    int sz = read(fd, r, file_size + writen);
    if (sz != -1)
    {
        r[sz] = '\0';
        printf("%s\n", r);
    }
    else
    {
        perror("Error reading from file");
        return errno;
    }
    close(fd);

    return 0;
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
    int length = strlen(string);
 
    int i = 0;
    for(i=0;i<length;i++){
        int digit = string[i] - '0';
        number = number * 10 + digit;
    }
 
    return number;
}