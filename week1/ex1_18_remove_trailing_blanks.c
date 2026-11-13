#include <stdio.h>

#define MAXLINE 1000

int get_line(char line[], int maxlen);
int trim(char line[], int len);

int main(void)
{

    int len;
    char line[MAXLINE];

    while ((len = get_line(line, MAXLINE)) > 0)
    {
        if (trim(line, len) > 0)
        {
            printf("%s", line);
        }
    }

    return 0;
}


int get_line(char line[], int maxlen)
{
    int c = 0;
    int i;
    for (i = 0; i < maxlen - 1 && (c = getchar()) != EOF && c != '\n'; i++ )
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

int trim(char line[], int len)
{
    int i = len - 1;

    if (i >= 0 && line[i] == '\n')
    {
        i--;
    }
    while (i >= 0 && (line[i] == ' ' || line[i] == '\t'))
    {
        i--;
    }

    if (i < 0)
    {
        return 0;
    }


    line[i + 1] = '\n';
    line[i + 2] = '\0';

    return i + 2;
}
