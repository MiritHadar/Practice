/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <iostream>
#include <cstdio>
#include "storage.hpp"
#include "packet.hpp"

using namespace std;
using namespace ilrd;

void BasicTest();
void PacketTest();
void FirstTest();
void SecondTest();
void NewTest();

int main()
{
	BasicTest();
	PacketTest();
	FirstTest();
	SecondTest();
	NewTest();

	return 0;
}

void BasicTest()
{
	unsigned char src[DATA_BLOCK_SIZE] = "write me!";
	unsigned char dest[DATA_BLOCK_SIZE] = "error";
	Storage strg;
	strg.Write(src, 0);
	strg.Read(dest, 0);
	cout << dest << endl;
}

void PacketTest()
{
	unsigned char src[DATA_BLOCK_SIZE] = "packet test";
	unsigned char dest[DATA_BLOCK_SIZE] = {0};

	Packet srcPkt(src);
	Packet destPkt(dest);
	Storage strg;
	strg.Write(srcPkt.GetBuffer(), 500);
	strg.Read(destPkt.GetBuffer(), 500);
	cout << destPkt.GetBuffer() << endl;
}

void FirstTest()
{
	Storage s;
	unsigned char array1[DATA_BLOCK_SIZE] = {0};
	unsigned char array2[DATA_BLOCK_SIZE] = {0};

	memset(array1, 'a', DATA_BLOCK_SIZE);
	s.Write(array1, 10);
	s.Read(array2, 10);

	for(size_t i = 0; i < DATA_BLOCK_SIZE; ++i)
	{
		if (array1[i] != array2[i] || 'a' != array2[i])
		{
			cout << "error in line " << __LINE__ << endl;
		}
	}
}

void SecondTest()
{
    Storage storage;

    for (size_t i = 0; i < 10; i++)
    {
        unsigned char data[DATA_BLOCK_SIZE] = {0};
        sprintf(reinterpret_cast<char*>(data), "%lu", i);
        storage.Write(data, i);
    }
    
    for (size_t i = 5; i < 10; i++)
    {
        unsigned char data[DATA_BLOCK_SIZE] = {0};
        sprintf(reinterpret_cast<char*>(data), "%lu", i + 10);
        storage.Write(data, i);
    }

    for (size_t i = 0; i < 10; i++)
    {
        unsigned char data[DATA_BLOCK_SIZE] = {0};
        storage.Read(data, i);
        printf("%s\n", data);
    }  
}

void NewTest()
{
	Storage s;
	unsigned char src[] = "lalalala";
	unsigned char dest[DATA_BLOCK_SIZE] = {0};
	s.Write(src, 0);
	s.Read(dest, 0);
	cout << dest << endl;
}


