#include <cs50.h>
#include <stdio.h>

int get_height(void);
void print_hashes(int n);

int main(void)
{
    int height = get_height();
    for (int row = 1; row <= height; row++)
    {
        for (int i = 0; i < height - row; i++)
        {
            printf(" ");
        }
        print_hashes(row);
        printf("  ");
        print_hashes(row);
        printf("\n");
    }

    return 0;
}

int get_height(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    return n;
}

void print_hashes(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
}
