/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_conversion
#define __OL67_conversion

#include <stdio.h>

typedef struct Person
{
    int age;
}Person;

typedef struct List 
{
    Person *person;
}List;

void Foo(List* ll, int key, int age);

void *ll_find(List* ll, int key);

#endif /* __OL67_conversion */


