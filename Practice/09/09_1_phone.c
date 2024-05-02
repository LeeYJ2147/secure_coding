#include <stdio.h>

int checking_phone(char *phone)
{
    int firstDash, secondDash;
    // find a index of first dash
    for (firstDash = 0; firstDash < sizeof(phone) && phone[firstDash] != '-'; firstDash++)
    {
    }
    switch (firstDash)
    {
    // case like 02-
    case 2:
        // {0}
        if (phone[0] != '0')
            return 0;
        // {1..9}
        if (phone[1] < '1' || phone[1] > '9')
            return 0;
        break;
    // case like 010-
    case 3:
        // {0}
        if (phone[0] != '0')
            return 0;
        // {1..9}
        if (phone[1] < '1' || phone[1] > '9')
            return 0;
        // [0..9]
        if (phone[2] < '0' || phone[1] > '9')
            return 0;
        break;
    // if the first dash format is not 02- or 010-
    default:
        return 0;
    }
    // find a index of second dash
    for (secondDash = firstDash + 1; secondDash < sizeof(phone) && phone[secondDash] != '-'; secondDash++)
    {
    }
    switch (secondDash - firstDash)
    {
    // case like 123-
    case 4:
        // {1..9}
        if (phone[firstDash + 1] < '1' || phone[firstDash + 1] > '9')
            return 0;
        // {0..9}2
        for (int i = 2; i < 4; i++)
            if (phone[firstDash + i] < '1' || phone[firstDash + i] > '9')
                return 0;
        break;
    // case like 1234-
    case 5:
        // {0..9}4
        for (int i = 1; i < 5; i++)
            if (phone[firstDash + i] < '1' || phone[firstDash + i] > '9')
                return 0;
        break;
    default:
        return 0;
    }
    // {0..9}4
    for (int i = 1; i < 5; i++)
        if (phone[secondDash + i] < '0' || phone[secondDash + i] > '9')
            return 0;
    return 1;
}

int main()
{
    int firstDash, secondDash;
    char phone[15];
    printf("Input number to check: ");
    if(scanf_str(phone, sizeof(phone))!=0)
    {
        puts("Invalid Inputs");
        return 1;
    }
    if (checking_phone(phone))
        puts("ok");
    else
        puts("not permitted");

    return 0;
}