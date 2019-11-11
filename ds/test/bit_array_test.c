
/*******************************************************************************
*	Description: Bit Array							   		         *
*	Author: Mirit Hadar									  	 	    *
*	Reviewer: Ada Elkin									 	 	    *
*	Status: Sent										 	  	    *
*	Last Update: 2/5/19										  	    *
*******************************************************************************/

#include <stdio.h>
#include "bit_array.h"

#define UNUSED_VAR(x) (void)(x)
#define MAX_LONG (unsigned long)0xFFFFFFFFFFFFFFFF


void BArrAllOnTest();
void BArrAllOffTest();
void BArrSetBitOnTest();
void BArrSetBitOffTest();
void BArrSetBitTest();
void BArrIsOnTest();
void BArrIsOffTest();
void BArrFlipBitTest();
void BArrRotateRTest();
void BArrRotateLTest();
void BArrMirrorTest();
void TestBArrCountOn();
void TestBArrCountOff();
void TestBArrPrintBits();
void TestBArrMirrorLUT();
void TestBArrCountOnLUT();

int main()
{
	BArrAllOnTest();
	BArrAllOffTest();
	BArrSetBitOnTest();
	BArrSetBitOffTest();
	BArrSetBitTest();
	BArrIsOnTest();	
	BArrIsOffTest();
	BArrFlipBitTest();
	BArrRotateRTest();
	BArrRotateLTest();
	BArrMirrorTest();
	TestBArrCountOn();
	TestBArrCountOff();
	/*TestBArrPrintBits();*/
	TestBArrMirrorLUT();
	TestBArrCountOnLUT();
	
	return 0;
}

void BArrAllOnTest()	/*Test all on*/
{
	if(0xFFFFFFFFFFFFFFFF != BArrAllOn())
	{
		puts("All On failed!");
	}
}

void BArrAllOffTest()	/*Test all off*/
{
	if(0 != (BArrAllOff()))
	{
		puts("All Off failed!");
	}
}

void BArrSetBitOnTest()			/*Set Bit On*/
{
	if (32 != BArrSetBitOn(0, 5))
	{
		puts("1 Set Bit On failed!");
	}

	if (0xFFFFFFFFFFFFFFFF != BArrSetBitOn(0xFFFFFFFFFFFFFFFF, 6))
	{
		puts("2 Set Bit On failed!");
	}

	if (0xc0 != BArrSetBitOn(0x80, 6))
	{
		puts("3 Set Bit On failed!");
	}
}


void BArrSetBitOffTest()			/*Set Bit Off*/
{
	if (0 != BArrSetBitOff(0, 5))
	{
		puts("1 Set Bit Off failed!");
	}

	if (0x7FFFFFFFFFFFFFFF != BArrSetBitOff(0xFFFFFFFFFFFFFFFF, 63))
	{
		puts("2 Set Bit Off failed!");
	}

	if (4 != BArrSetBitOff(12, 3))
	{
		puts("3 Set Bit Off failed!");
	}

}


void BArrSetBitTest()			/*Set Bit Off OR On*/
{
	/*turning on*/
	if (32 != BArrSetBit(0, 5, 1))	
	{
		puts("1 Set Bit On failed!");
	}

	if (0xFFFFFFFFFFFFFFFF != BArrSetBit(0xFFFFFFFFFFFFFFFF, 6, 100))
	{
		puts("2 Set Bit On failed!");
	}

	if (0xc0 != BArrSetBit(0x80, 6, 9))
	{
		puts("3 Set Bit On failed!");
	}


	/*turning off*/
	if (0 != BArrSetBit(0, 5, 0))		
	{
		puts("1 Set Bit Off failed!");
	}

	if (0x7FFFFFFFFFFFFFFF != BArrSetBit(0xFFFFFFFFFFFFFFFF, 63, 0))
	{
		puts("2 Set Bit Off failed!");
	}

	if (4 != BArrSetBit(12, 3, 0))
	{
		puts("3 Set Bit Off failed!");
	}
}


void BArrIsOnTest()			/*bit ON - returns 1*/
{
	if (1 != BArrIsOn(0xFFFFFFFFFFFFFFF0, 63))	
	{
		puts("1 Set Bit On failed!");
	}

	if (1 != BArrIsOn(0xAAAAAAAAAAAAAAA, 9))
	{
		puts("2 Set Bit On failed!");
	}

	if (0 != BArrIsOn(0xFFFFFFFFFFFFFFF0, 3))
	{
		puts("3 Set Bit On failed!");
	}

	if (0 != BArrIsOn(0, 50))		
	{
		puts("4 Set Bit Off failed!");
	}
}

void BArrIsOffTest()			/*bit OFF - returns 1*/
{
	if (0 != BArrIsOff(0xFFFFFFFFFFFFFFF0, 63))	
	{
		puts("1 Set Bit Off failed!");
	}

	if (0 != BArrIsOff(0xAAAAAAAAAAAAAAA, 9))
	{
		puts("2 Set Bit Off failed!");
	}

	if (1 != BArrIsOff(0xFFFFFFFFFFFFFFF0, 3))
	{
		puts("3 Set Bit Off failed!");
	}

	if (1 != BArrIsOff(0, 50))		
	{
		puts("4 Set Bit Off failed!");
	}
}


void BArrFlipBitTest()			/*Flip Bit*/
{
	/*printf("%lu\n", BArrFlipBit(12,2));*/

	if (8 != BArrFlipBit(12,2))	
	{
		puts("1 Flip Bit failed!");
	}

	if (0x7000000000000000 != BArrFlipBit(0xF000000000000000, 63))
	{
		puts("2 Flip Bit failed!");
	}

	if (1 != BArrFlipBit(0, 0))
	{
		puts("3 Flip Bit failed!");
	}

	if (0xEFFFFFFFFFFFFFFF != BArrFlipBit(0xFFFFFFFFFFFFFFFF, 60))		
	{
		puts("4 Flip Bit failed!");
	}
}


void BArrRotateRTest()			/*Rotate right*/
{
	if (0xE000000000000001 != BArrRotateR(0xF, 3))
	{
		puts("1 Rotate right failed!");
	}
	if (0xFFFFFFFFFFFFFFFF != BArrRotateR(0xFFFFFFFFFFFFFFFF, 86))
	{
		puts("2 Rotate right failed!");
	}
	if (0x0 != BArrRotateR(0x0, 20))
	{
		puts("3 Rotate right failed!");
	}
	if (0x3FC0000000000000 != BArrRotateR(0xFF, 10))
	{
		puts("4 Rotate right failed!");
	}

}

void BArrRotateLTest()			/*Rotate left*/
{
	if (0xFFEEDDCCBBAA9988 != BArrRotateL(0xFFEEDDCCBBAA9988,262144))
	{
		puts("1 Rotate left failed!");
	}
	if (0xBBAA9988FFEEDDCC != BArrRotateL(0xFFEEDDCCBBAA9988, 32))
	{
		puts("2 Rotate left failed!");
	}
	if (0x0 != BArrRotateL(0x0, 20))
	{
		puts("3 Rotate left failed!");
	}
	if (0xFFFFFFFFFFFFF807 != BArrRotateL(0xFFFFFFFFFFFFFF00, 3))
	{
		puts("4 Rotate left failed!");
	}
	if (0x1 != BArrRotateL(0x8000000000000000, 1))
	{
		puts("5 Rotate left failed!");
	}
}

void BArrMirrorTest()				/*mirror*/
{
	if (0x0100000000000000 != BArrMirror(0x80))
	{
		puts("1 Mirror failed!");
	}

	if (0x8000000000000000 != BArrMirror(0x1))
	{
		puts("BArrMirror fail 1");
	}

	if (MAX_LONG != BArrMirror(MAX_LONG))
	{
		puts("BArrMirror fail all on");
	}

	if (0x0000000000000000 != BArrMirror(0x0000000000000000))
	{
		puts("BArrMirror fail all off");
	}

	if (0xFFFFFFFF00000000 != BArrMirror(0x00000000FFFFFFFF))
	{
		puts("BArrMirror fail half same");
	}

}


void TestBArrCountOn()				/*count on*/
{
	if (40 != BArrCountOn(0x8899AABBCCDDEEFF))
	{
		puts("BArrCountOn fail 40");
	}
	if (29 != BArrCountOn(0xF839186ADE8B8A01))
	{
		puts("BArrCountOn fail 29");
	}
	if (64 != BArrCountOn(0xFFFFFFFFFFFFFFFF))
	{
		puts("BArrCountOn fail all on");
	}
	if (0 != BArrCountOn(0))
	{
		puts("BArrCountOn fail all off");
	}
	if (4 != BArrCountOn(15))
	{
		puts("BArrCountOn fail 4 on");
	}
	
}


void TestBArrCountOff()					/*count off*/
{
	if (24 != BArrCountOff(0x8899AABBCCDDEEFF))
	{
		puts("BArrCountOff fail 24");
	}
	if (35 != BArrCountOff(0xF839186ADE8B8A01))
	{
		puts("BArrCountOff fail 29");
	}
	if (0 != BArrCountOff(0xFFFFFFFFFFFFFFFF))
	{
		puts("BArrCountOff fail all on");
	}
	if (64 != BArrCountOff(0))
	{
		puts("BArrCountOff fail all off");
	}
	if (56 != BArrCountOff(255))
	{
		puts("BArrCountOff fail 8 on");
	}
}


void TestBArrPrintBits()
{
	puts("*******************Test Print Bits**************************");
	BArrPrintBits(0x8000000000000000);
	BArrPrintBits(0xFF);
	BArrPrintBits(0x1);
	BArrPrintBits(0xF);
	BArrPrintBits(MAX_LONG);
}

void TestBArrMirrorLUT()
{
	if (0x0100000000000000 != BArrMirrorLUT(0x80))
	{
		puts("1 Mirror LUT failed!");
	}


	if (0x8000000000000000 != BArrMirrorLUT(0x1))
	{
		puts("Mirror LUT fail 1");
	}


	if (MAX_LONG != BArrMirrorLUT(MAX_LONG))
	{
		puts("Mirror LUT fail all on");
	}

	if (0x0000000000000000 != BArrMirrorLUT(0x0000000000000000))
	{
		puts("Mirror LUT fail all off");
	}

	if (0xFFFFFFFF00000000 != BArrMirrorLUT(0x00000000FFFFFFFF))
	{
		puts("Mirror LUT fail half same");
	}

}

void TestBArrCountOnLUT()
{
	if (64 != BArrCountOnLUT(MAX_LONG))
	{
		puts("MAX_LONG Count On LUT failed!");
	}

	if (1 != BArrCountOnLUT(0x1))
	{
		puts("0x1 Count On LUT failed!");
	}

	if (4 != BArrCountOnLUT(0xF000000000000000))
	{
		puts("0xF000000000000000 Count On LUT failed!");
	}

	if (0 != BArrCountOnLUT(0x0))
	{
		puts("0x0 Count On LUT failed!");
	}

	if (32 != BArrCountOnLUT(0xFFFFFFFF00000000))
	{
		puts("0xFFFFFFFF00000000 Count On LUT failed!");
	}
	if (32 != BArrCountOnLUT(0xFFFFFFFF))
	{
		puts("0xFFFFFFFF Count On LUT failed!");
	}
}





