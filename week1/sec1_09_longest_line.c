#include <stdio.h>

#define MAXLINE 1000

int get_line(char line[], int maxline);
void copy(char to[], char from[]);

int main(void)
{
    // current line length
    int len;
    // maxium length seen so far
    int max = 0;
    // current input line
    char line[MAXLINE];
    // longest line saved here
    char longest[MAXLINE];

    while ((len = get_line(line, MAXLINE)) > 0)
    {
        if (len > max)
        {
            max = len;
            copy(longest, line);
        }
    }

    if (max > 0)
    {
        printf("Longest line: %s", longest);
    }

    return 0;
}

int get_line(char line[], int maxline)
{
    int c = 0;
    int i = 0;

    for (i = 0; i < maxline - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    {
        line[i] = c;
    }

    if (c == '\n')
    {
        line[i] = c;
        i++;
    }
    line[i] = '\0';
    return i;
}

void copy(char to[], char from[])
{
    int i = 0;
    while ((to[i] = from[i]) != '\0')
    {
        i++;
    }
}
