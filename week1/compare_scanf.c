#include <stdio.h>

int main(void)
{
	int x = 0;
	int y = 0;
	printf("What is x? ");
	scanf("%d", &x);
	printf("What is y? ");
	scanf("%d", &y);

	if (x > y)
	{
		printf("%d is greater than %d\n", x, y);
	}
	else if (x < y)
	{
		printf("%d is less than %d\n", x, y);
	}
	else
	{
		printf("%d is equal to %d\n", x, y);
	}

	return 0;
}
