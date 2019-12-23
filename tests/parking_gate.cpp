
#include <iostream>

using namespace std;

unsigned char g_systemController = 0;

void StartMotor(int direction);

int main()
{
    StartMotor(1);
    return 0;
}

void StartMotor(int direction)
{
    cout << 0x3 << endl;
    g_systemController &= (char)direction;
}