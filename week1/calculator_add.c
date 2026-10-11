#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int x = get_int("What is x? ");
    int y = get_int("What is y? ");

    printf("%d\n", x + y);

    return 0;
}
