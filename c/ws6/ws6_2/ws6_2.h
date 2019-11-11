
/******************************************************************************
*	Description: Bitwise operations - header file					   *
*	Author: Mirit Hadar							  			      			  *
*	Reviewer: Ori Michaeli										   *
*	Status: Sent						 					        *
*	Last Update: 21.4.19										   *
*******************************************************************************/


#ifndef __WS6_OL67
#define __WS6_OL67

unsigned char ByteMirorLoop(unsigned char byte);
unsigned char ByteMiror(unsigned char byte);
int AreBits2And6On(unsigned char byte);
int AreBits2Or6On(unsigned char byte);
int SwapBits3And5(unsigned char byte);
unsigned int ClosestDividedBy16(unsigned int);
void Swap(unsigned int *, unsigned int *);


#endif /*__WS6_OL67*/
