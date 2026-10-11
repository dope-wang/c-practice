#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int x = get_int("What's x? ");
    int y = get_int("What's y? ");

    printf("%d / %d = %d\n", x, y, x / y);

    return 0;
}
