#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int get_words(string s);
int get_letters(string s);
int get_sentences(string s);

int main(void)
{
    string text = get_string("Text: ");
    // get words by space
    int words = get_words(text);
    // get letters by alpha
    int letters = get_letters(text);
    // get by ? . !
    int sentence = get_sentences(text);
    // index = 0.0588 * L - 0.296 * S - 15.8
    float l = letters / (double)  words * 100;
    float s = sentence / (double) words * 100;
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

int get_words(string s)
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

int get_letters(string s)
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

int get_sentences(string s)
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
