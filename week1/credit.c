#include <cs50.h>
#include <stdio.h>

bool get_luhn(long l);
string valid_check(long l);
int get_length(long l);
int get_prefix(long l);

int main(void)
{
    long number = get_long("Number: ");
    if (get_luhn(number))
    {
        printf("%s\n", valid_check(number));
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}

bool get_luhn(long l)
{
    long l2 = l;
    int result = 0;

    while (l > 0)
    {
        l /= 10;
        int digit = l % 10 * 2;
        if (digit > 9)
        {
            result += digit / 10;
            result += digit % 10;
        }
        else
        {
            result += digit;
        }
        l /= 10;
    }

    while (l2 > 0)
    {
        result += l2 % 10;
        l2 /= 100;
    }

    return result % 10 == 0;
}

string valid_check(long l)
{
    int prefix = get_prefix(l);
    int len = get_length(l);
    if (len == 15 && (prefix == 34 || prefix == 37))
    {
        return "AMEX";
    }
    else if (len == 16 && (prefix >=  51 && prefix <= 55))
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

int get_length(long l)
{
    int len = 1;

    while (l >= 10)
    {
        l /= 10;
        len += 1;
    }
    return len;
}

int get_prefix(long l)
{
    while (l >= 100)
    {
        l /= 10;
    }
    return (int) l;
}
