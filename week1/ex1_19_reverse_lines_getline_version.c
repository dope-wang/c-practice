#include <stdio.h>

#define MAXLINE 1000

int get_line(char line[], int maxline);
void reverse(char arr[]);

int main(void)
{
    // current line length
    int len;
    // current input line
    char line[MAXLINE];


    while ((len = get_line(line, MAXLINE)) > 0)
    {

        reverse(line);
        printf("%s", line);
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

void reverse(char arr[])
{
    int len = 0;
    while (arr[len] != '\0')
    {
        len++;
    }
    int left = 0;
    int right = len - 1;

    if (right >= 0 && arr[right] == '\n')
    {
       right--;
     }

    while (left < right)
    {
        int tmp = arr[right];
        arr[right] = arr[left];
        arr[left] = tmp;
        right--;
        left++;
    }
}
