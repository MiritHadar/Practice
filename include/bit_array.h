/*******************************************************************************
*	Description: Bit Array							  	  		    *
*	Author: Mirit Hadar									  		    *
*	Reviewer: Ada Elkin										 	    *
*	Status: Sent										  		    *
*	Last Update: 2/5/19											    *
*******************************************************************************/


#ifndef OL67_BIT_ARR		
							
#define OL67_BIT_ARR

unsigned long BArrAllOn(void);
unsigned long BArrAllOff(void);
unsigned long BArrSetBitOn(unsigned long num, size_t index);
unsigned long BArrSetBitOff(unsigned long num, size_t index);
unsigned long BArrSetBit(unsigned long num, size_t index, int state);
int BArrIsOn(unsigned long num, size_t index);
int BArrIsOff(unsigned long num, size_t index);
unsigned long BArrFlipBit(unsigned long num, size_t index);
unsigned long BArrRotateR(unsigned long num, size_t shitfs);
unsigned long BArrRotateL(unsigned long num, size_t shitfs);
unsigned long BArrMirror(unsigned long num);
size_t BArrCountOn(unsigned long num);
size_t BArrCountOff(unsigned long num);
void BArrPrintBits(unsigned long num);

unsigned long BArrMirrorLUT(unsigned long num);
size_t BArrCountOnLUT(unsigned long num);

#endif /* OL67_BIT_ARR */
