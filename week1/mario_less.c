#include <cs50.h>
#include <stdio.h>

int check_height(void);

int main(void)
{
    int height = check_height();

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
        printf("\n");
    }

    return 0;
}

int check_height(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1);

    return n;
}
