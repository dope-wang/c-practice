#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int numbers[] = {20, 500, 10, 5, 100, 1, 50};
    int n = get_int("Number: ");
    // sizeof(numbers) = 28 (4 * 7), sizeof(numbers[0]) = 4 (1個 int 佔 4 bytes)
    int len = sizeof(numbers) / sizeof(numbers[0]);
    for (int i = 0; i < len; i++)
    {
        if (numbers[i] == n)
        {
            printf("Found at index %i!\n", i);
            return 0;
        }
    }
    printf("Not Found!\n");
    return 1;
}
