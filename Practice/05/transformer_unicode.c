#include <stdio.h>
#include <stdlib.h>

#define MAX_UTFBIN_SIZE 33
#define MAX_UNIBIN_SIZE 25

// ----------<def Stack>----------
typedef char element;
typedef struct {
    element data[MAX_UTFBIN_SIZE];
    int top;
} StackType;

void initStack(StackType *S) {
    S->top = -1;
}

int isEmpty(StackType *S) {
    return (S->top == -1);
}

int isFull(StackType *S) {
    return (S->top >= MAX_UNIBIN_SIZE-1);
}

void push(StackType *S, element e) {
    if(isFull(S)) {return;}
    S->data[++(S->top)] = e;
}

element pop(StackType *S) {
    if(isEmpty(S)) exit(1);
    return S->data[(S->top)--];
}
// ----------</def Stack>----------

int UniToU8(unsigned int Unicode, char *UTF_8_result) {
    /*
     * process:
     *  1. transform Unicode(16) into Unicode(2)
     *  2. transform Unicode(2) into UTF-8(2)
     *     -> divide according to Unicode range
     *     -> different processing (as shown in the pdf) 
     *        is performed for each divided area
     *  3. transform UTF-8(2) into UTF-8(16)
     * return: 0(none error), 1(error occured)
     */

    // UTF Encoding result in binary bit using Big Endian
    char UTF_binary[MAX_UTFBIN_SIZE];
    // trans Unicode into binary bit using Little Endian
    StackType *Uni_binary = (StackType *)malloc(sizeof(StackType));

    // init
    for(int i=0; i<MAX_UTFBIN_SIZE; i++) UTF_binary[i] = '0';
    initStack(Uni_binary);

    // [process-1] Unicode(16) -> Unicode(2)
    for(int i=0; i<MAX_UNIBIN_SIZE; i++)
        push(Uni_binary, ((Unicode >> i) & 1) + '0');

    // [process-2] Unicode(2) -> UTF-8(2)
    if(Unicode < 1<<7) {
        int i;
        Uni_binary->top = 7;

        for(i=0; i<8; i++) UTF_binary[i] = pop(Uni_binary);

        UTF_binary[i] = '\0';
    } else if(Unicode < 1<<11) {
        int i;
        Uni_binary->top = 11;

        UTF_binary[0] = '1', UTF_binary[1] = '1';
        for(i=2; i<8; i++) UTF_binary[i] = (char)pop(Uni_binary);

        UTF_binary[8] = '1', UTF_binary[9] = '0';
        for(i=10; i<16; i++) UTF_binary[i] = (char)pop(Uni_binary);

        UTF_binary[i] = '\0';
    } else if(Unicode < 1<<16) {
        int i;
        Uni_binary->top = 15;

        UTF_binary[0] = '1', UTF_binary[1] = '1';
        UTF_binary[2] = '1', UTF_binary[3] = '0';
        for(i=4; i<8; i++) UTF_binary[i] = (char)pop(Uni_binary);

        UTF_binary[8] = '1', UTF_binary[9] = '0';
        for(i=10; i<16; i++) UTF_binary[i] = (char)pop(Uni_binary);

        UTF_binary[16] = '1', UTF_binary[17] = '0';
        for(i=18; i<24; i++) UTF_binary[i] = (char)pop(Uni_binary);

        UTF_binary[i] = '\0';
    } else if(Unicode < 1114112) {
        int i;
        Uni_binary->top = 20;

        UTF_binary[0] = '1', UTF_binary[1] = '1';
        UTF_binary[2] = '1', UTF_binary[3] = '1', UTF_binary[4] = '0';
        for(i=5; i<8; i++) UTF_binary[i] = (char)pop(Uni_binary);

        UTF_binary[8] = '1', UTF_binary[9] = '0';
        for(i=10; i<16; i++) UTF_binary[i] = (char)pop(Uni_binary);

        UTF_binary[16] = '1', UTF_binary[17] = '0';
        for(i=18; i<24; i++) UTF_binary[i] = (char)pop(Uni_binary);

        UTF_binary[24] = '1', UTF_binary[25] = '0';
        for(i=26; i<32; i++) UTF_binary[i] = (char)pop(Uni_binary);

        UTF_binary[i] = '\0';
    } else { /* Unicode Input Error. Out of range */
        free(Uni_binary);
        return 1;
    }

    // [process-3] UTF-8(2) -> UTF-8(16)
    int i;
    for(i=0; i<8 && UTF_binary[4*i] != '\0'; i++) {
        int decimal=0;

        for(int j=0; j<4 && UTF_binary[4*i+j] != '\0'; j++) {
            decimal = (decimal << 1) | (UTF_binary[4*i+j] - '0');
        }

        if(decimal < 10) UTF_8_result[i] = '0'+decimal;
        else UTF_8_result[i] = 'A'+(decimal-10);
    }
    UTF_8_result[i] = '\0';
    free(Uni_binary);
    return 0;
}

int UniToU16BE(unsigned int Unicode, char *UTF_16_result) {
    /*
     * process:
     *  1. transform Unicode(16) into Unicode(2)
     *  2. transform Unicode(2) into UTF-16(2)
     *     -> divide according to Unicode range
     *     -> different processing (as shown in the pdf) 
     *        is performed for each divided area
     *  3. transform UTF-16(2) into UTF-16(16)
     * return: 0(none error), 1(error occured)
     */

    // UTF Encoding result in binary bit using Big Endian
    char UTF_binary[MAX_UTFBIN_SIZE];
    // trans Unicode into binary bit using Little Endian
    StackType *Uni_binary = (StackType *)malloc(sizeof(StackType));
    unsigned int temp = Unicode;

    // init
    for(int i=0; i<MAX_UTFBIN_SIZE; i++) UTF_binary[i] = '0';
    initStack(Uni_binary);

    // [process-1] UTF-16 surrogate
    if(Unicode >= 1<<16 && Unicode < 1114112) temp -= 0x010000;

    // Unicode(16) -> Unicode(2)
    for(int i=0; i<MAX_UNIBIN_SIZE; i++)
        push(Uni_binary, ((temp >> i) & 1) + '0');

    // [process-2] Unicode(2) -> UTF-16(2)
    if(Unicode < 1<<7) {
        int i;
        Uni_binary->top = 7;

        for(i=8; i<16; i++) UTF_binary[i] = pop(Uni_binary);

        UTF_binary[i] = '\0';
    } else if(Unicode < 1<<11) {
        int i;
        Uni_binary->top = 11;
        
        for(i=4; i<16; i++) UTF_binary[i] = (char)pop(Uni_binary);

        UTF_binary[i] = '\0';
    } else if(Unicode < 1<<16) {
        int i;
        Uni_binary->top = 15;

        for(i=0; i<16; i++) UTF_binary[i] = (char)pop(Uni_binary);

        UTF_binary[i] = '\0';
    } else if(Unicode < 1114112) {
        int i;
        Uni_binary->top = 19;

        UTF_binary[0] = '1', UTF_binary[1] = '1', UTF_binary[2] = '0';
        UTF_binary[3] = '1', UTF_binary[4] = '1', UTF_binary[5] = '0';
        for(i=6; i<16; i++) UTF_binary[i] = (char)pop(Uni_binary);

        UTF_binary[16] = '1', UTF_binary[17] = '1', UTF_binary[18] = '0';
        UTF_binary[19] = '1', UTF_binary[20] = '1', UTF_binary[21] = '1';
        for(i=22; i<32; i++) UTF_binary[i] = (char)pop(Uni_binary);

        UTF_binary[i] = '\0';
    } else { /* Unicode Input Error. Out of range */
        free(Uni_binary);
        return 1;
    }

    // [process-3] UTF-16(2) -> UTF-16(16)
    int i;
    for(i=0; i<8 && UTF_binary[4*i] != '\0'; i++) {
        int decimal=0;
        
        for(int j=0; j<4 && UTF_binary[4*i+j] != '\0'; j++) {
            decimal = (decimal << 1) | (UTF_binary[4*i+j] - '0');
        }
        if(decimal < 10) UTF_16_result[i] = '0'+decimal;
        else UTF_16_result[i] = 'A'+(decimal-10);
    }
    UTF_16_result[i] = '\0';
    free(Uni_binary);
    return 0;
}

int U8ToUni(unsigned int UTF8, char *Unicode_result) {
    /*
     * process:
     *  1. transform UTF-8 into Decimal
     *  2. transform Decimal into Unicode
     * return: 0(none error), 1(error occured)
     */

    // [process-1] UTF-8 -> Decimal
    if(UTF8 < 1<<7) {
    } else if(UTF8 < 1<<16) {
        UTF8-=0b1100000010000000;
        unsigned int temp = 0;
        temp += UTF8%(1<<6);
        temp += ((UTF8%(1<<13))>>8)<<6;
        UTF8 = temp;
    } else if(UTF8 < 1<<24) {
        UTF8-=0b111000001000000010000000;
        unsigned int temp = 0;
        temp += UTF8%(1<<6);
        temp += ((UTF8%(1<<14))>>8)<<6;
        temp += ((UTF8%(1<<20))>>16)<<12;
        UTF8 = temp;
    } else if(UTF8 < 0b11111000000000000000000000000000) {
        UTF8-=0b11110000100000001000000010000000;
        unsigned int temp = 0;
        temp += UTF8%(1<<6);
        temp += ((UTF8%(1<<14))>>8)<<6;
        temp += ((UTF8%(1<<22))>>16)<<12;
        temp += ((UTF8%(1<<27))>>24)<<18;
        UTF8 = temp;
    } else {
        return 1;
    }
    
    // [process-2] Decimal -> Unicode
    int i, range = UTF8<0x10000?2:0;
    for(i=range; i<6; i++) {
        int decimal=0;

        for(int j=0; j<4; j++)
            decimal = (decimal << 1) | ((UTF8>>(23-4*i-j)) & 1);
        if(decimal < 10) Unicode_result[i-range] = '0'+decimal;
        else Unicode_result[i-range] = 'A'+(decimal-10);
    }
    Unicode_result[i-range] = '\0';
    return 0;
}

int U8ToU16BE(unsigned int UTF8, char *UTF_16_result) {
    /*
     * process:
     *  1. transform UTF-8 into Decimal
     *  2. transform Decimal into UTF-16BE
     * return: 0(none error), 1(error occured)
     */

    // [process-1] UTF-8 -> Decimal
    if(UTF8 < 1<<7) {
    } else if(UTF8 < 1<<16) {
        UTF8-=0b1100000010000000;
        unsigned int temp = 0;
        temp += UTF8%(1<<6);
        temp += ((UTF8%(1<<13))>>8)<<6;
        UTF8 = temp;
    } else if(UTF8 < 1<<24) {
        UTF8-=0b111000001000000010000000;
        unsigned int temp = 0;
        temp += UTF8%(1<<6);
        temp += ((UTF8%(1<<14))>>8)<<6;
        temp += ((UTF8%(1<<20))>>16)<<12;
        UTF8 = temp;
    } else if(UTF8 < 0b11111000000000000000000000000000) {
        UTF8-=0b11110000100000001000000010000000;
        unsigned int temp = 0;
        temp += UTF8%(1<<6);
        temp += ((UTF8%(1<<14))>>8)<<6;
        temp += ((UTF8%(1<<22))>>16)<<12;
        temp += ((UTF8%(1<<27))>>24)<<18;
        UTF8 = temp;
    } else {
        return 1;
    }
    
    // [process-2] Decimal (-> Unicode) -> UTF-16
    if(UniToU16BE(UTF8, UTF_16_result) == 0) return 0;
    return 1;
}

int U16BEToUni(unsigned int UTF16, char *Unicode_result) {
    /*
     * process:
     *  1. transform UTF-16BE into Decimal
     *  2. transform Decimal into Unicode
     * return: 0(none error), 1(error occured)
     */

    // [process-1] UTF-16BE -> Decimal
    if(UTF16 < 2<<23) {
    } else if(UTF16 < 0b11111000000000000000000000000000) {
        UTF16-=0b11011000000000001101110000000000;
        UTF16+=1<<22;
        unsigned int temp = 0;
        temp += UTF16%(1<<10);
        temp += ((UTF16%(1<<27))>>16)<<10;
        UTF16 = temp;
    } else {
        return 1;
    }
    
    // [process-2] Decimal -> Unicode
    int i, range = UTF16<0x10000?2:0;
    for(i=0; i<6; i++) {
        int decimal=0;

        for(int j=0; j<4; j++)
            decimal = (decimal << 1) | ((UTF16>>(23-4*i-j)) & 1);
        if(decimal < 10) Unicode_result[i-range] = '0'+decimal;
        else Unicode_result[i-range] = 'A'+(decimal-10);
    }
    Unicode_result[i-range] = '\0';
    return 0;
}

int U16BEToU8(unsigned int UTF16, char *UTF_8_result) {
    /*
     * process:
     *  1. transform UTF-16BE into Decimal
     *  2. transform Decimal into UTF-8
     * return: 0(none error), 1(error occured)
     */

    // [process-1] UTF-16BE -> Decimal
    if(UTF16 < 2<<23) {
    } else if(UTF16 < 0b11111000000000000000000000000000) {
        UTF16-=0b11011000000000001101110000000000;
        UTF16+=1<<22;
        unsigned int temp = 0;
        temp += UTF16%(1<<10);
        temp += ((UTF16%(1<<27))>>16)<<10;
        UTF16 = temp;
    } else {
        return 1;
    }

    // [process-2] Decimal (-> Unicode) -> UTF-8
    if(UniToU8(UTF16, UTF_8_result) == 0) return 0;
    return 1;
}

int UTF8Checker(unsigned int UTF8) {
    int byteCount = 0;
    int condition1, condition2, condition3;
    if((UTF8 & 0xF0000000) == 0xF0000000) {
        /* 1111 0000 0000 0000 0000 0000 0000 0000 */
        byteCount = 4;
    } else if((UTF8 & 0xE00000) == 0xE00000) {
        /* 0000 0000 1110 0000 0000 0000 0000 0000 */
        byteCount = 3;
    } else if((UTF8 & 0xC000) == 0xC000) {
        /* 0000 0000 0000 0000 1100 0000 0000 0000 */
        byteCount = 2;
    } else {
        byteCount = 1;
    }

    // Check the validity of the UTF-8 sequence
    switch (byteCount) {
        case 1:
            // Single-byte characters: 0xxxxxxx
            condition1 = (UTF8 & 0x80) == 0;
            // min: 0x00 (trivial)
            // max: 0x80 (is encodinged over 0x7F)
            condition3 = UTF8 < 0x80;
            return condition1 && condition3;
        case 2:
            // Two-byte characters: 110xxxxx 10xxxxxx
            condition1 = (UTF8 & 0xE0C0) == 0xC080;
            // min: 0xC280 (is encodinged under 0x80)
            condition2 = UTF8 >= 0xC280;
            // max: 0xCFC0 (is encodinged over 0x7FF)
            condition3 = UTF8 < 0xCFC0;
            return condition1 && condition2 && condition3;
        case 3:
            // Three-byte characters: 1110xxxx 10xxxxxx 10xxxxxx
            condition1 = (UTF8 & 0xF0C0C0) == 0xE08080;
            // min: 0xE0A080 (is encodinged under 0x800)
            condition2 = UTF8 >= 0xE0A080;
            // max: 0xEFBFC0 (is encodinged over 0xFFFF)
            condition3 = UTF8 < 0xEFBFC0;
            return condition1 && condition2 && condition3;
        case 4:
            // Four-byte characters: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
            condition1 = (UTF8 & 0xF8C0C0C0) == 0xF0808080;
            // min: 0xF0908080
            condition2 = UTF8 >= 0xF0908080;
            // max: 0xF48FBFC0
            condition3 = UTF8 < 0xF48FBFC0;
            return condition1 && condition2 && condition3;
        default:
            return 0;
    }
}

int main() {
    puts("------------------------------");
    puts("Unicode <-> UTF-8 <-> UTF-16BE");
    puts("------------------------------\n");

    while(1) {
        char userInput[10];
        int userSelect;
        unsigned int userTrans;
        char transRes[9] = "00000000";

        puts("---------------- Select Menu ----------------");
        puts("[1] Unicode -> UTF-8\t[2] Unicode -> UTF-16BE");
        puts("[3] UTF-8   -> Unicode\t[4] UTF-8   -> UTF-16BE");
        puts("[5] UTF-16  -> Unicode\t[6] UTF-16  -> UTF-8");
        puts("[7] UTF-8 Checker     \t[8] Quit");
        printf(">>> ");
        scanf("%s", userInput);
        userSelect = userInput[0]-'0';

        switch(userSelect) {
            case 1:
                /* Unicode -> UTF-8 */
                printf("Input Unicode(ex. U+000000)\n>>> U+");
                scanf("%X", &userTrans);

                if(UniToU8(userTrans, transRes)==0) {
                    printf("[UTF-8] 0x%s\n\n", transRes);
                } else {
                    printf("** INVAILID INPUT **\n");
                    printf("Please Check Your Inputs\n");
                }

                break;
            case 2:
                /* Unicode -> UTF-16BE */
                printf("Input Unicode(ex. U+000000)\n>>> U+");
                scanf("%X", &userTrans);

                if(UniToU16BE(userTrans, transRes)==0) {
                    printf("[UTF-16] 0x%s\n\n", transRes);
                } else {
                    printf("** INVAILID INPUT **\n");
                    printf("Please Check Your Inputs\n");
                }

                break;
            case 3:
                /* UTF-8 -> Unicode */
                printf("Input UTF-8(ex. 0x00000000)\n>>> 0x");
                scanf("%X", &userTrans);

                if(U8ToUni(userTrans, transRes)==0) {
                    printf("[Unicode] U+%s\n\n", transRes);
                } else {
                    printf("** INVAILID INPUT **\n");
                    printf("Please Check Your Inputs\n");
                }

                break;
            case 4:
                /* UTF-8 -> UTF-16BE */
                printf("Input UTF-8(ex. 0x00000000)\n>>> 0x");
                scanf("%X", &userTrans);

                if(U8ToU16BE(userTrans, transRes)==0) {
                    printf("[UTF-16] 0x%s\n\n", transRes);
                } else {
                    printf("** INVAILID INPUT **\n");
                    printf("Please Check Your Inputs\n");
                }

                break;
            case 5:
                /* UTF-16BE -> Unicode */
                printf("Input UTF-16(ex. 0x00000000)\n>>> 0x");
                scanf("%X", &userTrans);

                if(U16BEToUni(userTrans, transRes)==0) {
                    printf("[Unicode] U+%s\n\n", transRes);
                } else {
                    printf("** INVAILID INPUT **\n");
                    printf("Please Check Your Inputs\n");
                }

                break;
            case 6:
                /* UTF-16BE -> UTF-8 */
                printf("Input UTF-16(ex. 0x00000000)\n>>> 0x");
                scanf("%X", &userTrans);

                if(U16BEToU8(userTrans, transRes)==0) {
                    printf("[UTF-8] 0x%s\n\n", transRes);
                } else {
                    printf("** INVAILID INPUT **\n");
                    printf("Please Check Your Inputs\n");
                }

                break;
            case 7:
                /* UTF-8 Checker */
                printf("Input UTF-8(ex. 0x00000000)\n>>> 0x");
                scanf("%X", &userTrans);

                if(UTF8Checker(userTrans)) {
                    puts("The UTF-8 sequence is valid.\n");
                } else {
                    puts("The UTF-8 sequence is not valid.\n");
                }

                break;
            case 8:
                return 0;
            default:
                printf("** INVAILID INPUT **\n");
                printf("Please Check Your Inputs\n");
                break;
        }
    }
}