/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <iostream>
#include "packet.hpp"

using namespace std;
using namespace ilrd;

void PacketTest();

int main()
{
    PacketTest();
}

void PacketTest()
{
    unsigned char buff[BUFF_SIZE] = "this is my packet";
    Packet packet(buff);
    
    cout << packet.GetBuffer() << endl;
    //cout << packet.GetActType() << endl;
}
