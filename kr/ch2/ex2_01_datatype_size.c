#include <float.h>
#include <limits.h>
#include <stdio.h>

int main(void)
{
    printf("Float min: %f\n", FLT_MIN);
    printf("Float max: %f\n", FLT_MAX);

    printf("----------------------\n");

    printf("Double min: %f\n", DBL_MIN);
    printf("Double max: %f\n", DBL_MAX);

    printf("----------------------\n");

    printf("Char min: %d\n", CHAR_MIN);
    printf("Char max: %d\n", CHAR_MAX);
    printf("Signed char min: %d\n", SCHAR_MIN);
    printf("Signed char max: %d\n", SCHAR_MAX);
    printf("Unsigned char max: %d\n", UCHAR_MAX);

    printf("----------------------\n");

    printf("Signed int min: %d\n", INT_MIN);
    printf("Signed int max: %d\n", INT_MAX);
    printf("Unsigned int max: %u\n", UINT_MAX);

    printf("----------------------\n");

    printf("Signed short min: %d\n", SHRT_MIN);
    printf("Signed short max: %d\n", SHRT_MAX);
    printf("Unsigned short max: %d\n", USHRT_MAX);

    printf("----------------------\n");

    printf("Signed long min: %ld\n", LONG_MIN);
    printf("Signed long max: %ld\n", LONG_MAX);
    printf("Unsigned long max: %lu\n", ULONG_MAX);

    return 0;
}
