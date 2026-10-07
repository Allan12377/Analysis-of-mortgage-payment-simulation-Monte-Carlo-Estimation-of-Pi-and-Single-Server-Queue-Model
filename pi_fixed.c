/* Program to estimate Pi using Monte Carlo simulation - Fixed version */
/* Original had non-standard srandom/random and DEBUG always on */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SEED 1234567  /* initial seed for PRNG */

int main(void)
{
    int i, num;
    double x, y, z, pi;
    int count; /* points within upper-right quadrant of unit circle */

    printf("Enter the number of iterations to use in estimating pi: ");
    if (scanf("%d", &num) != 1 || num <= 0) {
        printf("Invalid number of iterations.\n");
        return 1;
    }

    /* initialize random numbers - use standard C rand/srand */
    srand(SEED);  

    /* do the Monte Carlo simulation */
    count = 0;
    for (i = 0; i < num; i++)
    {
        /* generate a uniformly random U(0,1) point in x-y dimensions */
        x = (double) rand() / RAND_MAX;
        y = (double) rand() / RAND_MAX;

        /* compute z = x^2 + y^2 */
        z = x * x + y * y;

        /* see if it is inside the unit circle or not */
        if (z <= 1.0)
        {
            count++;
        }
    }

    /* scale the estimate back up to the full circle */
    pi = 4.0 * (double) count / (double) num;
    
    printf("Number of trials: %d\n", num);
    printf("Estimate of pi: %g\n", pi);
    printf("True value of pi is approximately 3.1415926535\n");
    return 0;
}
