#include <stdarg.h>
#include <stdio.h>

void print_numbers(int count, ...) {
    va_list args;
    va_start(args, count); // 가변 인수 목록 초기화
    for (int i = 0; i < count; i++) {
        int value = va_arg(args, int); // 현재 가변 인수를 읽고, 다음 인수로 이동
        printf("%d ", value);
    }
    va_end(args); // 가변 인수 목록 정리
}

int main() {
    print_numbers(5, 1, 2, 3, 4, 5);
    return 0;
}