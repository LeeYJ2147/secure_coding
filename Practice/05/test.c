#include <stdio.h>

int main() {
    int i;
    unsigned int UTF8 = 0x0041;
    printf("%d\n", UTF8);
    
    for(i=0; i<6; i++) {
        int decimal=0;

        for(int j=0; j<4; j++) {
            decimal = (decimal << 1) | ((UTF8>>(23-4*i-j)) & 1);
            printf("%d ", ((UTF8>>(23-4*i-j)) & 1));
        }
        printf("\n[testing] %x %d\n", decimal, decimal);
    }
}
//0000 0101 0101 1111
