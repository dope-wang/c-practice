#include <cs50.h>
#include <stdio.h>

bool pass_luhn(long num);
string card_type(long num);
int get_length(long num);
int get_prefix(long num);

int main(void)
{
    long number = get_long("Number: ");
    if (pass_luhn(number))
    {
        printf("%s\n", card_type(number));
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}

bool pass_luhn(long num)
{
    long l2 = num;
    int result = 0;

    while (num > 0)
    {
        num /= 10;
        int digit = num % 10 * 2;
        if (digit > 9)
        {
            result += digit / 10;
            result += digit % 10;
        }
        else
        {
            result += digit;
        }
        num /= 10;
    }

    while (l2 > 0)
    {
        result += l2 % 10;
        l2 /= 100;
    }

    return result % 10 == 0;
}

string card_type(long num)
{
    int prefix = get_prefix(num);
    int len = get_length(num);
    if (len == 15 && (prefix == 34 || prefix == 37))
    {
        return "AMEX";
    }
    else if (len == 16 && (prefix >= 51 && prefix <= 55))
    {
        return "MASTERCARD";
    }
    else if ((len == 13 || len == 16) && prefix / 10 == 4)
    {
        return "VISA";
    }
    else
    {
        return "INVALID";
    }
}

int get_length(long num)
{
    int len = 1;

    while (num >= 10)
    {
        num /= 10;
        len += 1;
    }
    return len;
}

int get_prefix(long num)
{
    while (num >= 100)
    {
        num /= 10;
    }
    return (int) num;
}
