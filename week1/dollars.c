#include <cs50.h>
#include <limits.h>
#include <stdio.h>

int main(void)
{
    int dollars = 1;

    while (true)
    {
	char c = get_char("Here's $%d, double it or give to next person? ", dollars);
	if (c == 'y')
	{
	    if (dollars > INT_MAX / 2)
	    {
		printf("Too much money!\n");
	    }
	    dollars *= 2;
	}
	else
	{
	    break;
	}
    }

    return 0;
}

