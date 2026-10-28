#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool check_digit(string s1, string s2);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }
    if (!check_digit(argv[0], argv[1]))
    {
        return 1;
    }
    int n = atoi(argv[1]);

    int remainder = n % 26;
    string input = get_string("plaintext:  ");

    printf("ciphertext: ");
    for (int i = 0, j = strlen(input); i < j; i++)
    {
        if (isalpha(input[i]))
        {
            if (isupper(input[i]))
            {
                printf("%c", (input[i] - 'A' + remainder) % 26 + 65);
            }
            else
            {
                printf("%c", (input[i] - 'a' + remainder) % 26 + 97);
            }
        }
        else
        {
            printf("%c", input[i]);
        }
    }
    printf("\n");
    return 0;
}

bool check_digit(string s1, string s2)
{
    for (int i = 0, n = strlen(s2); i < n; i++)
    {
        if (!isdigit(s2[i]))
        {
            printf("Usage: %s key\n", s1);
            return false;
        }
    }
    return true;
}
