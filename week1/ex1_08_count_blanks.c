#include <stdio.h>

int main(void)
{
    int blank = 0;
    int tab = 0;
    int newline = 0;

    int c;

    while ((c = getchar()) != EOF)
    {
        if (c == ' ')
        {
            blank++;
        }
        else if (c == '\t')
        {
            tab++;
        }
        else if (c == '\n')
        {
            newline++;
        }
    }

    printf("blank: %d\n", blank);
    printf("tab: %d\n", tab);
    printf("newline: %d\n", newline);

    return 0;
}
