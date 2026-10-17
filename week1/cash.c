#include <cs50.h>
#include <stdio.h>

int get_change(void);

int main(void)
{
    int change = get_change();
    int count = 0;

    count += change / 25;
    change %= 25;

    count += change / 10;
    change %= 10;

    count += change / 5;
    change %= 5;

    count += change;
    printf("%d\n", count);

    return 0;
}

int get_change(void)
{
    int change;
    do
    {
        change = get_int("Change owed: ");
    }
    while (change < 0);

    return change;
}
