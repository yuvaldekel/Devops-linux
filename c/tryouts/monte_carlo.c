#include <stdio.h> 
#include <stdlib.h>
#include <math.h>


int main(int argc, char *argv[])
{
    int n = 5000000;
    int inside = 0;

    for(int i=0;i<n;i++)
    {
        double x = ((float) rand() * 2 / RAND_MAX) - 1;
        double y = ((float) rand() * 2 / RAND_MAX) - 1;

        double sqr_x = pow(x, 2);
        double sqr_y = pow(y, 2);
        double distance = sqrt(sqr_x + sqr_y);

        if (distance <= 1)
        {
            inside++;
        }
    }

    double pi = 4 * ((double) inside / n);
    printf("%f\n", pi);
}