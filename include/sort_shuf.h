
#ifndef OL67_SORT_SHUF	
#define OL67_SORT_SHUF

#include <stddef.h>     /* size_t */

typedef int (*cmp_t)(const void *, const void *, void *param);

int Shuf(int argc, char **argv);

#endif	/*	OL67_SORT_SHUF  */
