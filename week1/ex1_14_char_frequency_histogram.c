#include <stdio.h>

#define NCHARS 256

void print_frequency(int n);

int main(void)
{
    int c;
    int count[NCHARS] = {0};

    while ((c = getchar()) != EOF)
    {
        count[c]++;
    }

    for (int i = 0; i < NCHARS; i++)
    {
        if (count[i] > 0)
        {
            if (i == '\n')
            {
                printf("\\n | ");
            }
            else if (i == '\t')
            {
                printf("\\t | ");
            }
            else if (i == ' ')
            {
                printf("SP | ");
            }
            else
            {
                printf("%c | ", i);
            }

            print_frequency(count[i]);
            printf("\n");
        }
    }

    return 0;
}

void print_frequency(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("*");
    }
}
