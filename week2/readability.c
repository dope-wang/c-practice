#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_words(string s);
int count_letters(string s);
int count_sentences(string s);

int main(void)
{
    string text = get_string("Text: ");
    // get words by space
    int words = count_words(text);
    // get letters by alpha
    int letters = count_letters(text);
    // get by ? . !
    int sentences = count_sentences(text);
    // index = 0.0588 * L - 0.296 * S - 15.8
    double l = letters / (double) words * 100;
    double s = sentences / (double) words * 100;
    int index = round(0.0588 * l - 0.296 * s - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", index);
    }

    return 0;
}

int count_words(string s)
{
    int result = 1;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] == ' ')
        {
            result++;
        }
    }
    return result;
}

int count_letters(string s)
{
    int result = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (isalpha(s[i]))
        {
            result++;
        }
    }
    return result;
}

int count_sentences(string s)
{
    int result = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] == '.' || s[i] == '?' || s[i] == '!')
        {
            result++;
        }
    }
    return result;
}
