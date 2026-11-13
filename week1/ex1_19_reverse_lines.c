#include <stdio.h>

#define MAXLINE 1000

int reverse(char input[], int maxline);

int main(void)
{
    int len = 0;
    char input[MAXLINE];

    while ((len = reverse(input, MAXLINE)) > 0)
    {
        printf("Result: %s", input);
    }

    return 0;
}

int reverse(char input[], int maxline)
{
    int i = 0;
    int c = 0;
    while (i < maxline - 1 &&(c = getchar()) != EOF)
    {
        if (c == '\n')
        {
            break;
        }
        input[i++] = c;
    }

    int j = 0;
    int k = i -1;

    while (j < k)
    {
        int temp = input[k];
        input[k] = input[j];
        input[j] = temp;
        j++;
        k--;
    }

    if (c == '\n')
    {
        input[i] = '\n';
        i++;
    }
    input[i] = '\0';
    return i;
}
