#include <stdio.h>

int main(void)
{
	char c = 'A';
	printf("字元 %c 數值: %d\n", c, c);
	printf("字元 A + 1 = %d\n", c + 1);

	printf("A size: %zu\n", sizeof(c));
	printf("char: %zu \n", sizeof(char));
	printf("int: %zu \n", sizeof(int));
	printf("long: %zu \n", sizeof(long));

	return 0;
}
