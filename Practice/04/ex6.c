#include <stdio.h>
#include <memory.h>
#include <string.h>
#define EXP_BIT_SIZE 8
#define MANTISSA_BIT_SIZE 23

union ieee754_singleprecision {
    float f_a;
    struct struct_ieee754_singleprecision_t {
        unsigned int mantissa : 23; // mantissa
        unsigned int exp : 8; // exponent
        int sign : 1; // sign
    } floatData; // IEEE754SinglePrecision
} floatVal; // float_IEEE754

void GetBitString(unsigned int value, int size, char* str_out)
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
    floatVal.f_a = 0.875f;
    char sign_bit, exp_bit_str[EXP_BIT_SIZE + 1], mantissa_bit_str[MANTISSA_BIT_SIZE + 1];
    char bitString[EXP_BIT_SIZE + MANTISSA_BIT_SIZE + 1];

    printf("sign : %c\n", floatVal.floatData.sign == 0 ? '+' : '-');
    printf("exponent : 0X%X\n", floatVal.floatData.exp);
    printf("mantissa : 0X%X\n", floatVal.floatData.mantissa);

    sign_bit = floatVal.floatData.sign == 0 ? '0' : '1';
    GetBitString(floatVal.floatData.exp, EXP_BIT_SIZE , exp_bit_str);
    GetBitString(floatVal.floatData.mantissa, MANTISSA_BIT_SIZE, mantissa_bit_str);

    printf("%c / %s / %s\n", sign_bit, exp_bit_str, mantissa_bit_str);
    
    // <추가한 내용>
    unsigned char cpy_float_val[4]={0};
    memcpy(cpy_float_val, &floatVal.floatData, sizeof(floatVal.floatData));
    for(int i=sizeof(floatVal.floatData)-1; i>=0; i--) {
        // little endian -> 역으로 접근
        for(int j=8-1; j>=0; j--) { // 8비트 출력
            printf("%d", cpy_float_val[i]>>j&1 ? 1:0);
            if(cpy_float_val[i] >> j & 1) printf("1");
            else printf("0");
        }
        printf(" ");
    }
    printf("\n");
    // </추가한 내용>

    // 부호변환전
    printf("\nBefore changed sign bit :%f\n", floatVal.f_a);

    // 부호변환후
    floatVal.floatData.sign = 1;

    printf("sign : %c\n", floatVal.floatData.sign == 0 ? '+' : '-');
    printf("exponent : 0X%X\n", floatVal.floatData.exp);
    printf("mantissa : 0X%X\n", floatVal.floatData.mantissa);

    sign_bit = floatVal.floatData.sign == 0 ? '0' : '1';
    GetBitString(floatVal.floatData.exp, EXP_BIT_SIZE , exp_bit_str);
    GetBitString(floatVal.floatData.mantissa, MANTISSA_BIT_SIZE, mantissa_bit_str);

    printf("%c / %s / %s\n", sign_bit, exp_bit_str, mantissa_bit_str);
    
    // <추가한 내용>
    memcpy(cpy_float_val, &floatVal.floatData, sizeof(floatVal.floatData));
    for(int i=sizeof(floatVal.floatData)-1; i>=0; i--) {
        // little endian -> 역으로 접근
        for(int j=8-1; j>=0; j--) { // 8비트 출력
            if(cpy_float_val[i] >> j & 1) printf("1");
            else printf("0");
        }
        printf(" ");
    }
    printf("\n");
    // </추가한 내용>

    printf("\nAfter changed sign bit :%f\n", floatVal.f_a);
    
    return 0;
}