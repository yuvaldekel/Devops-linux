#include <dirent.h> 
#include <stdio.h> 


int main(void) {
    
    DIR *d;
    struct dirent *dir;

    d = opendir("./trysuid");

    if (d) {
        dir = readdir(d);

        while (dir != NULL)
        {
            printf("%s\n", dir->d_name);
            dir = readdir(d);
        }
        
        closedir(d);
    }

    return(0);
}