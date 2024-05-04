// 201 0 3456 > 2001-12-3456
// 201 1 3456 > 2001-11-3456
// {2}{0}{0..9}{0..1}{0..9}4

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


int v_sprintf(char *buffer, const char *format, ...) {
    int n;
    va_list args;
    va_start(args, format);
    n = vsprintf(buffer, format, args);
    va_end(args);
    return n;
}

int v_asprintf(char **str, const char *format, ...) {
    int n;
    va_list args;
    va_start(args, format);
    n = vasprintf(str, format, args);
    va_end(args);
    return n;
}

int v_snprintf(char *buffer, size_t size, const char *format, ...) {
    int n;
    va_list args;
    va_start(args, format);
    n = vsnprintf(buffer, size, format, args);
    va_end(args);
    return n;
}

int main()
{
    int n;
    char b[13], sp[13], *asp, snp[13];
    scanf("%s", b);

    puts("\n# sprintf");
    n = sprintf(sp, "%c0%c%c-1%c-%c%c%c%c", b[0], b[1], b[2], '2'-b[3]+'0', b[4], b[5], b[6], b[7]);
    printf("%d:%s\n", n, sp);

    puts("\n# asprintf-1");
    n=asprintf(&asp, "%c0%c%c-1%c-%c%c%c%c", b[0], b[1], b[2], '2'-b[3]+'0', b[4], b[5], b[6], b[7]);
    printf("%d:%s\n", n, asp);
    free(asp);
    asp = NULL;

    puts("\n# asprintf-2");
    n=asprintf(&asp, "%c0%c%c-1%c-%c%c%c%c%100000000000s", b[0], b[1], b[2], '2'-b[3]+'0', b[4], b[5], b[6], b[7], b);
    printf("%d:%s\n", n, asp);
    free(asp);
    asp = NULL;
    
    puts("\n# snprintf-1");
    n = snprintf(snp, sizeof(snp), "%c0%c%c-1%c-%c%c%c%c", b[0], b[1], b[2], '2'-b[3]+'0', b[4], b[5], b[6], b[7]);
    printf("%d:%s\n", n, snp);
    
    puts("\n# snprintf-2");
    n = snprintf(snp, sizeof(snp), "%c0%c%c-1%c-%c%c%c%c%100000000000s", b[0], b[1], b[2], '2'-b[3]+'0', b[4], b[5], b[6], b[7], b);
    printf("%d:%s\n", n, snp);
    // ------
    puts("\n# vsprintf");
    n = v_sprintf(sp, "%c0%c%c-1%c-%c%c%c%c", b[0], b[1], b[2], '2'-b[3]+'0', b[4], b[5], b[6], b[7]);
    printf("%d:%s\n", n, sp);

    puts("\n# vasprintf-1");
    n = v_asprintf(&asp, "%c0%c%c-1%c-%c%c%c%c", b[0], b[1], b[2], '2'-b[3]+'0', b[4], b[5], b[6], b[7]);
    printf("%d:%s\n", n, asp);
    free(asp);
    asp = NULL;

    puts("\n# vasprintf-2");
    n = v_asprintf(&asp, "%c0%c%c-1%c-%c%c%c%c%100000000000s", b[0], b[1], b[2], '2'-b[3]+'0', b[4], b[5], b[6], b[7], b);
    printf("%d:%s\n", n, asp);
    free(asp);
    asp = NULL;
    
    puts("\n# vsnprintf-1");
    n = v_snprintf(snp, sizeof(snp), "%c0%c%c-1%c-%c%c%c%c", b[0], b[1], b[2], '2'-b[3]+'0', b[4], b[5], b[6], b[7]);
    printf("%d:%s\n", n, snp);
    
    puts("\n# vsnprintf-2");
    n = v_snprintf(snp, sizeof(snp), "%c0%c%c-1%c-%c%c%c%c%100000000000s", b[0], b[1], b[2], '2'-b[3]+'0', b[4], b[5], b[6], b[7], b);
    printf("%d:%s\n", n, snp);

}