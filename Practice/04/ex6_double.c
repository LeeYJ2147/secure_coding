#include <stdio.h>
#include <memory.h>
#include <string.h>
#define EXP_BIT_SIZE 11
#define MANTISSA_BIT_SIZE 52

union ieee754_doubleprecision {
    double d_a;
    struct struct_ieee754_doubleprecision_t {
        unsigned long long mantissa : 52; // mantissa
        // 오답임 unsigned int exp : 11; // exponent
        unsigned long long exp : 11;
        // 오답임 int sign : 1; // sign
        unsigned long long sign : 1;
    } doubleData; // IEEE754SinglePrecision
} doubleVal; // double_IEEE754

void GetBitString(unsigned long long value, int size, char* str_out)
{
    int i;
    for (i = 0; i < size; i++) { // 1001010111101010010
        if (value >> (size - i - 1) & 1) {
            str_out[i] = '1';
        }
        else {
            str_out[i] = '0';
        }
    }
    str_out[i] = '\0';
}

int main()
{
    doubleVal.d_a = 0.875;
    char sign_bit, exp_bit_str[EXP_BIT_SIZE + 1], mantissa_bit_str[MANTISSA_BIT_SIZE + 1];
    char bitString[EXP_BIT_SIZE + MANTISSA_BIT_SIZE + 1];

    printf("sign : %c\n", doubleVal.doubleData.sign == 0 ? '+' : '-');
    printf("exponent : 0X%X\n", doubleVal.doubleData.exp);
    printf("mantissa : 0X%llX\n", doubleVal.doubleData.mantissa);

    sign_bit = doubleVal.doubleData.sign == 0 ? '0' : '1';
    GetBitString(doubleVal.doubleData.exp, EXP_BIT_SIZE , exp_bit_str);
    GetBitString(doubleVal.doubleData.mantissa, MANTISSA_BIT_SIZE, mantissa_bit_str);

    printf("%c / %s / %s\n", sign_bit, exp_bit_str, mantissa_bit_str);

    // 부호변환전
    printf("\nBefore changed sign bit :%f\n", doubleVal.d_a);

    // 부호변환후
    doubleVal.doubleData.sign = 1;

    printf("sign : %c\n", doubleVal.doubleData.sign == 0 ? '+' : '-');
    printf("exponent : 0X%X\n", doubleVal.doubleData.exp);
    printf("mantissa : 0X%llX\n", doubleVal.doubleData.mantissa);

    sign_bit = doubleVal.doubleData.sign == 0 ? '0' : '1';
    GetBitString(doubleVal.doubleData.exp, EXP_BIT_SIZE , exp_bit_str);
    GetBitString(doubleVal.doubleData.mantissa, MANTISSA_BIT_SIZE, mantissa_bit_str);

    printf("%c / %s / %s\n", sign_bit, exp_bit_str, mantissa_bit_str);

    printf("\nAfter changed sign bit :%f\n", doubleVal.d_a);
    
    return 0;
}