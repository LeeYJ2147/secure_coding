#include <stdio.h>

int checking_phone(char *phone)
{
    int firstDash, secondDash;

    for (firstDash = 0; firstDash < sizeof(phone) && phone[firstDash] != '-'; firstDash++)
    {
    }
    switch (firstDash)
    {
    case 2:
        if (phone[0] != '0')
            return 0;
        if (phone[1] < '1' || phone[1] > '9')
            return 0;
        break;
    case 3:
        if (phone[0] != '0')
            return 0;
        if (phone[1] < '1' || phone[1] > '9')
            return 0;
        if (phone[2] < '0' || phone[1] > '9')
            return 0;
        break;
    default:
        return 0;
    }

    for (secondDash = firstDash + 1; secondDash < sizeof(phone) && phone[secondDash] != '-'; secondDash++)
    {
    }
    switch (secondDash - firstDash)
    {
    case 4:
        for (int i = 1; i < 4; i++)
            if (phone[firstDash + i] < '1' || phone[firstDash + i] > '9')
                return 0;
        break;
    case 5:
        for (int i = 1; i < 5; i++)
            if (phone[firstDash + i] < '1' || phone[firstDash + i] > '9')
                return 0;
        break;
    default:
        return 0;
    }
    for (int i = 1; i < 5; i++)
        if (phone[secondDash + i] < '0' || phone[secondDash + i] > '9')
            return 0;
    return 1;
}

int main()
{
    int firstDash, secondDash;
    char phone[15];
    puts("Input number to check: ");
    gets(phone);
    if(checking_phone(phone)) puts("ok");
    else puts("not permitted");
    
    return 0;
}