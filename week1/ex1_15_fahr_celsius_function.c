#include <stdio.h>

#define UPPER 300
#define STEP 20
#define LOWER 0

double fahr_to_celsius(double fahr);

int main(void)
{
    for (int fahr = LOWER; fahr <= UPPER; fahr += STEP)
    {
        printf("%3d %6.1f\n", fahr, fahr_to_celsius(fahr));
    }
    return 0;
}


double fahr_to_celsius(double fahr)
{
    return (5.0 / 9.0) * (fahr - 32.0);
}
