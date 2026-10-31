#include <stdio.h>

int main(void)
{
    int c;
    int lastchar = 0;
    while ((c = getchar()) != EOF)
    {
        if (lastchar != ' ' || c != ' ')
        {
            putchar(c);
        }
        lastchar = c;
    }

    return 0;
}
