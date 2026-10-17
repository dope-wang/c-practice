#include <cs50.h>
#include <stdio.h>

int get_heights(void);

int main(void)
{
    int height = get_heights();
    for (int row = 1; row <= height; row++)
    {
        for (int i = 0; i < height - row; i++)
        {
            printf(" ");
        }
        for (int i = 0; i < row; i++)
        {
            printf("#");
        }
        printf("  ");
        for (int i = 0; i < row; i++)
        {
            printf("#");
        }
        printf("\n");
    }

    return 0;
}

int get_heights(void)
{
    int n;
    do
    {
        n = get_int("Heights: ");
    }
    while (n < 1 || n > 8);

    return n;
}
