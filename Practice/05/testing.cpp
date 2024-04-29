#include <iostream>

using namespace std;

int main()
{
    int X;

    cout << "Enter Number (Decimal) : ";
    cin >> X;

    cout << "to Binary : ";
    for (int i = 7; i >= 0; i--)
    {
        int temp = (X >> i) & 1;
        cout << temp;
    }

    cout << X;
    
    return 0;
}