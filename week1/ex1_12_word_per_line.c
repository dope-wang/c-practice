#include <stdbool.h>
#include <stdio.h>

int main(void)
{
    int c;
    bool in_word = false;

    while ((c = getchar()) != EOF)
    {
        if (c == ' ' || c == '\t' || c == '\n')
        {
            if (in_word)
            {
                printf("\n");
            }
            in_word = false;
        }
        else
        {
            putchar(c);
            in_word = true;
        }
    }

    return 0;
}
