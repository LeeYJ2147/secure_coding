#include <stdio.h>

int main()
{
    int permitted=1, firstDash, secondDash;
    char phone[15];
    puts("Input number to check: ");
    gets_s(phone, sizeof(phone));

    for(firstDash=0; firstDash<sizeof(phone) && phone[firstDash]!='-'; firstDash++) {}
    switch(firstDash){
        case 2:
            if(phone[0] != '0') {permitted=0; return permitted;}
            else if(phone[1])
        case 3:
        default:
            permitted=0;
            return permitted;
    }
}