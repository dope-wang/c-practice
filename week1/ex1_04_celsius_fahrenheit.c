#include <stdio.h>

int main(void)
{
    // F = (C * (9.0/5.0)) + 32
    float celsius, fahr;
    int lower, upper, step;

    lower = 0;

    upper = 300;
    step = 20;
    celsius = lower;

    printf("%7s %10s\n", "Celsius", "Fahrenheit");
    while (celsius <= upper)
    {
        fahr = (celsius * (9.0 / 5.0)) + 32;
        printf("%7.0f %10.0f\n", celsius, fahr);
        celsius += step;
    }

    return 0;
}
