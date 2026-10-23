#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Missing CLI Argument\n");
        printf("Usage: %s name\n", argv[0]);
        fprintf(stderr, "Usage: %s name\n", argv[0]);
        return 1;
    }

    printf("Hello, %s\n", argv[1]);
    return 0;
}
