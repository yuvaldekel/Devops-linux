#include <dirent.h> 
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

extern int errno;

int list_files(void);

int main(int argc, char *argv[]) {

    int next = list_files();

    char str_next[2];
    sprintf(str_next, "%i", next);
    char name[] = "./trysuid/test";

    char *path = strcat(name, str_next);
    int result = mkdir(path, 0775);

    if (errno == 13)
    {   
        printf("Permission denied\n");
    }

    return errno;
}

int list_files(void) {
    
    int count = 0;
    DIR *d;
    struct dirent *dir;

    d = opendir("./trysuid");

    if (d) {
        dir = readdir(d);

        while (dir != NULL)
        {
            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0 && dir->d_type == 4) 
            {
                count++;
            }

            dir = readdir(d);
        }
        
        closedir(d);
    }

    return count;
}