#include <ctype.h>
#include <stdio.h>

#define MAXLEN 9

void print_bar(int n);
void check_length(int num[], int length);

int main(void)
{
    int c;
    int length = 0;
    int len[10] = {0};
    while ((c = getchar()) != EOF)
    {
        if (!isspace(c))
        {
            length++;
        }
        else
        {
            check_length(len, length);
            length = 0;
        }
    }

    check_length(len, length);
    length = 0;

    for (int i = 1; i < 10; i++)
    {
        if (i < MAXLEN)
        {
            printf("%d | ", i);
        }
        else
        {
            printf("9+ | ");
        }
        print_bar(len[i]);
        printf("\n");
    }
    return 0;
}

void print_bar(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("*");
    }
}

void check_length(int num[], int length)
{
    if (length > MAXLEN)
    {
        num[MAXLEN]++;
    }
    else if (length > 0)
    {
        num[length]++;
    }
}
