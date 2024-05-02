#include <stdio.h>

int check_range(char target, char start, char end)
{
    return target < start || target > end;
}

int checking_classNumber(char *classNumber)
{
    // {[A-Z]|[a-z]}3
    for (int i = 0; i < 3; i++)
        if (check_range(classNumber[i], 'A', 'z'))
            return 0;
    // {1-4}
    if (check_range(classNumber[3], '1', '4'))
        return 0;
    // {0-9}3
    for (int i = 4; i < 7; i++)
        if (check_range(classNumber[i], '0', '9'))
            return 0;
    // {-}
    if (classNumber[7] != '-')
        return 0;
    // {0-1}
    if (check_range(classNumber[8], '0', '1'))
        return 0;
    // {0-9}
    if (check_range(classNumber[9], '0', '9'))
        return 0;

    return 1;
}

int scanf_str(char *toSave, int term)
{
    int i=0;
    while(i<term)
    {
        char temp;
        scanf("%c", &temp);
        if(temp == '\0' || temp == '\n') return 0;
        else toSave[i++] = temp;
    }
    return 1;
}

int main()
{
    char classNumber[15];
    puts("Input classNumber to check: ");
    if(scanf_str(classNumber, sizeof(classNumber))!=0)
    {
        puts("Invalid Inputs");
        return 1;
    }
    if (checking_classNumber(classNumber))
        puts("ok");
    else
        puts("not permitted");

    return 0;
}