#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int i = 3;
    while (i > 0)
    {
        printf("meow\n");
        i--;
    }

    for (int k = 0; k < 3; k++)
    {
        printf("meow\n");
    }

    int n;

    while (true)
    {
        n = get_int("What is n? ");

        if (n >= 0)
        {
	    break;
	}
    }

    for (int j = 0; j < n; j++)
    {
	printf("meow\n");
    }


    return 0;
}
