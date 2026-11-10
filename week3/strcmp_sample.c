#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string a = get_string("a: ");
    string b = get_string("b: ");
    string c = a;

    printf("a 的位址: %p\n", (void *) a);
    printf("b 的位址: %p\n", (void *) b);
    printf("c 的位址: %p\n", (void *) c);

    printf("-----------------------------\n");

    printf("a == b: %d\n", a == b);
    printf("strcmp(a, b) == 0: %d\n", strcmp(a, b) == 0);
    printf("a == c: %d\n", a == c);
    return 0;
}
