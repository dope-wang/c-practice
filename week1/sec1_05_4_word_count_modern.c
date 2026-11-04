#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

int main(void)
{
    int c;
    int nl = 0;
    int nw = 0;
    long nc = 0;
    bool in_word = false;

    while ((c = getchar()) != EOF)
    {
        nc++;
        if (c == '\n')
        {
            nl++;
        }
        if (isspace(c))
        {
            in_word = false;
        }
        else if (!in_word)
        {
            in_word = true;
            nw++;
        }
    }
    printf("nl: %d nw: %d nc: %ld\n", nl, nw, nc);
    return 0;
}
