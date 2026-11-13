#include <stdio.h>

#define MAXLINE 1000
#define LIMIT 80

int get_line(char line[], int maxline);

int main(void)
{
    // current line length
    int len;
    // current input line
    char line[MAXLINE];

    while ((len = get_line(line, MAXLINE)) > 0)
    {
        // 加上 \n
        if (len > LIMIT + 1)
        {
            printf("80+ Line: %s", line);
        }
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

