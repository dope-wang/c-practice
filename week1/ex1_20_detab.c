#include <stdio.h>

#define TABSTOP 8

int main(void)
{
    int c = 0;
    int count = 0;


    while ((c = getchar()) != EOF)
    {
        if (c == '\t')
        {
            int space = TABSTOP - (count % TABSTOP);
            for (int i = 0; i < space; i++)
            {
                putchar(' ');
            }
            count += space;
        }
        else if (c == '\n')
        {
            putchar(c);
            count = 0;
        }
        else
        {
            putchar(c);
            count++;
        }

    }

    return 0;
}
