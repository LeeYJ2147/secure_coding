#include <stdio.h>

int main(void) {
    /*
    int i;
    for(i=0; i<10; i++) printf("%d ", i);
    printf("\n%d\n", i);
    return 0;
    */
   int value, size;
   printf("input value: ");
   scanf("%d", &value);
   size = 10;
   for(int i=0; i<size; i++) {
        if (value >> (size - i - 1) & 1) {
            printf("1");
        }
        else {
            printf("0");
        }
   }
}