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
    char format[21] = "%c0%c%c-1%c-%c%c%c%c";
    char long_format[35] = "%c0%c%c-1%c-%c%c%c%c%100000000000s";
    scanf("%s", b);

    puts("\n# sprintf");
    n = sprintf(sp, format, b[0], b[1], b[2], '2'-b[3]+'0', b[4], b[5], b[6], b[7]);
    printf("%d:%s\n", n, sp);

    puts("\n# asprintf-1");
    n=asprintf(&asp, format, b[0], b[1], b[2], '2'-b[3]+'0', b[4], b[5], b[6], b[7]);
    printf("%d:%s\n", n, asp);
    free(asp);
    asp = NULL;

    puts("\n# asprintf-2");
    n=asprintf(&asp, long_format, b[0], b[1], b[2], '2'-b[3]+'0', b[4], b[5], b[6], b[7], b);
    printf("%d:%s\n", n, asp);
    free(asp);
    asp = NULL;
    
    puts("\n# snprintf-1");
    n = snprintf(snp, sizeof(snp), format, b[0], b[1], b[2], '2'-b[3]+'0', b[4], b[5], b[6], b[7]);
    printf("%d:%s\n", n, snp);
    
    puts("\n# snprintf-2");
    n = snprintf(snp, sizeof(snp), long_format, b[0], b[1], b[2], '2'-b[3]+'0', b[4], b[5], b[6], b[7], b);
    printf("%d:%s\n", n, snp);
    // ------
    puts("\n# vsprintf");
    n = v_sprintf(sp, format, b[0], b[1], b[2], '2'-b[3]+'0', b[4], b[5], b[6], b[7]);
    printf("%d:%s\n", n, sp);

    puts("\n# vasprintf-1");
    n = v_asprintf(&asp, format, b[0], b[1], b[2], '2'-b[3]+'0', b[4], b[5], b[6], b[7]);
    printf("%d:%s\n", n, asp);
    free(asp);
    asp = NULL;

    puts("\n# vasprintf-2");
    n = v_asprintf(&asp, long_format, b[0], b[1], b[2], '2'-b[3]+'0', b[4], b[5], b[6], b[7], b);
    printf("%d:%s\n", n, asp);
    free(asp);
    asp = NULL;
    
    puts("\n# vsnprintf-1");
    n = v_snprintf(snp, sizeof(snp), format, b[0], b[1], b[2], '2'-b[3]+'0', b[4], b[5], b[6], b[7]);
    printf("%d:%s\n", n, snp);
    
    puts("\n# vsnprintf-2");
    n = v_snprintf(snp, sizeof(snp), long_format, b[0], b[1], b[2], '2'-b[3]+'0', b[4], b[5], b[6], b[7], b);
    printf("%d:%s\n", n, snp);

}