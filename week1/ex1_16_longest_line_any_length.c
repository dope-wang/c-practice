#include <stdio.h>

#define MAXLINE 10

int get_line(char line[], int maxline);
void copy(char to[], char from[]);

int main(void)
{
    int len;
    int max = 0;
    int sum = 0;
    char line[MAXLINE];
    char longest[MAXLINE];
    char first[MAXLINE];

    while ((len = get_line(line, MAXLINE)) > 0)
    {

        if (sum == 0)
        {
            copy(first, line);
        }
        sum += len;
        if (line[len - 1] == '\n')
        {
            if (sum > max)
            {
                max = sum;
                copy(longest, first);
            }
            // 讀取完 reset 0
            sum = 0;
        }
    }

    if (sum > max)
    {
        max = sum;
        copy(longest, first);
    }

    if (max > 0)
    {
        printf("Length: %d\n", max);
        if (max >= MAXLINE)
        {
            printf("Text: %s...\n", longest);
        }
        else
        {
            printf("Text: %s\n", longest);
        }
    }
    return 0;
}

int get_line(char line[], int maxline)
{
    int c = 0;
    int i;
    for (i = 0; i < maxline - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    {
        line[i] = c;
    }

    if (c == '\n')
    {
        line[i] = '\n';
        i++;
    }
    line[i] = '\0';

    return i;
}

void copy(char to[], char from[])
{
    int i = 0;
    do
    {
        to[i] = from[i];
    } while (from[i++] != '\0');

}
