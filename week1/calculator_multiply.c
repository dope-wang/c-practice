#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int x = get_int("What is x? ");

    printf("%d\n", x * 2);

    return 0;
}
