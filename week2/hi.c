#include <cs50.h>
#include <stdio.h>

int main(void)
{
    char c1 = 'H';
    char c2 = 'I';
    char c3 = '!';
    string s = "HI!";

    printf("%d %d %d\n", c1, c2, c3);
    printf("%c %c %c\n", s[0], s[1], s[2]);
    printf("%d %d %d\n", s[0], s[1], s[2]);
    printf("%d %d %d %d\n", s[0], s[1], s[2], s[3]);
    printf("%d %d %d %d %d\n", s[0], s[1], s[2], s[3], s[4]);
    printf("%c %c %c %c\n", s[4], s[5], s[6], s[7]);
    return 0;
}
