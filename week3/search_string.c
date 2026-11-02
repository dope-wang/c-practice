#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string strings[] = {"battleship", "boot", "cannon", "iron", "thimble", "top hat"};
    string s = get_string("String: ");
    int len = sizeof(strings) / sizeof(strings[0]);
    for (int i = 0; i < len; i++)
    {
        if (strcmp(strings[i], s) == 0)
        {
            printf("Found!\n");
            return 0;
        }
    }
    printf("Not Found!\n");
    return 1;
}
