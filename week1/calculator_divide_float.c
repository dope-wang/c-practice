#include <cs50.h>
#include <stdio.h>

int main(void)
{
    float x = get_float("What is x? ");
    float y = get_float("What is y? ");

    printf("%f / %f = %.20f\n", x, y, x / y);

    return 0;
}
