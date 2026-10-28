#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int alpha_array[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1,
                    3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int calculate_score(string s);

int main(void)
{
    string p1 = get_string("Player 1: ");
    string p2 = get_string("Player 2: ");

    int score1 = calculate_score(p1);
    int score2 = calculate_score(p2);

    if (score1 > score2)
    {
        printf("Player 1 wins!");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!");
    }
    else
    {
        printf("Tie!");
    }
    printf("\n");

    return 0;
}


int calculate_score(string s)
{
    int sum = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (isalpha(s[i]))
        {
            sum += alpha_array[toupper(s[i]) - 'A'];
        }
    }
    return sum;
}
