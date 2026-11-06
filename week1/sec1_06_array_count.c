#include <ctype.h>
#include <stdio.h>

/* count digits, white space, others  */
int main(void)
{
    int c;
    int nwhite = 0;
    int nother = 0;
    int ndigit[10] = {0};

    while ((c = getchar()) != EOF)
    {
        if (isdigit(c))
        {
            ndigit[c - '0']++;
        }
        else if (isspace(c))
        {
            nwhite++;
        }
        else
        {
            nother++;
        }
    }

    printf("digits: ");
    for (int i = 0; i < 10; i++)
    {
        printf("%d", ndigit[i]);
    }

    printf(", white space: %d, other: %d\n", nwhite, nother);

    return 0;
}
