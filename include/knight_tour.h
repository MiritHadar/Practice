

#ifndef OL67_KNIGHT_TOUR	
#define OL67_KNIGHT_TOUR

#include <stddef.h>           /* size_t */
#define		SIZE	                     5
#define		BITS_ROW	                 8
#define		BITS_COLUMN	                 8
#define     LEFT_ONE    0x8000000000000000
#define     RIGHT_ONE                  0x1
#define     WAYS_TO_PROCEED              8


/*Regular Implementation*/
void KTPrintBoard();
int KTPlayNaive(int i, int j, size_t counter);
int KTPlaySmart(int i, int j, size_t counter);

/*Bits Implementation*/
int KTPlaySmartBits(int i, int j, size_t counter_bits);
void KTPrintBitBoard();
void KTPrintBitPath();


#endif	/*	OL67_KNIGHT_TOUR  */
