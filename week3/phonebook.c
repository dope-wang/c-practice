#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string names[] = {"Kelly", "David", "John"};
    string numbers[] = {"+1-617-495-1000", "+1-617-495-1000", "+1-949-468-2750"};

    string s = get_string("Name: ");
    int len = sizeof(names) / sizeof(names[0]);
    for (int i = 0; i < len; i++)
    {
        if (strcmp(names[i], s) == 0)
        {
            printf("Found number: %s\n", numbers[i]);
            return 0;
        }
    }
    printf("Not Found!\n");
    return 1;
}

