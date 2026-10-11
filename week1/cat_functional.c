#include <cs50.h>
#include <stdio.h>

// Prototype

int get_n(void);
void meow(int times);

int main(void)
{
    // get a number from user
    int n = get_n();
    meow(n);

    return 0;
}

int get_n(void)
{
    int n;
    do
    {
	n = get_int("What is n? ");
    }
    while (n < 0);

    return n;
}

void meow(int times)
{
    for (int i = 0; i < times; i++)
    {
	printf("meow\n");
    }
}
