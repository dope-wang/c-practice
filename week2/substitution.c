#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool check_alpha(string s1, string s2);

int main(int argc, string argv[])
{

    if (argc != 2)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }
    string key = argv[1];
    if (!check_alpha(argv[0], key))
    {
        return 1;
    }

    int len = strlen(key);
    if (len != 26)
    {
        printf("INVALID INPUT!\n");
        return 1;
    }
    int cArr[26] = {0};
    char keyArr[26];
    for (int i = 0; i < 26; i++)
    {
        cArr[toupper(key[i]) - 'A']++;
        keyArr[i] = toupper(key[i]);
    }
    for (int i = 0; i < 26; i++)
    {
        if (cArr[i] != 1)
        {
            printf("INVALID INPUT!\n");
            return 1;
        }
    }
    string input = get_string("plaintext:  ");
    printf("ciphertext: ");
    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (isalpha(input[i]))
        {
            if (isupper(input[i]))
            {
                printf("%c", keyArr[input[i] - 'A']);
            }
            else
            {
                printf("%c", tolower(keyArr[input[i] - 'a']));
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

bool check_alpha(string s1, string s2)
{
    for (int i = 0, n = strlen(s2); i < n; i++)
    {
        if (!isalpha(s2[i]))
        {
            printf("Usage: %s key\n", s1);
            return false;
        }
    }
    return true;
}
