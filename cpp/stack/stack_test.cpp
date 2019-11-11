/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <cstdio>    /*	printf, puts 	*/

#include "stack.hpp" /*	Header file		*/
#include "str.hpp"   /* Str header      */

void TestDoubleInStack();
void TestStrInStack();

int main()
 {
    TestDoubleInStack();
    TestStrInStack();

    return 0;
}

void TestDoubleInStack()
{
    Stack<double> stack;

    if (!stack.IsEmpty())
    {
        printf("error in line %d\n", __LINE__);
    }

    if (0 != stack.Count())
    {
        printf("error in line %d\n", __LINE__);
    }

    stack.Push(1.5);
    if (stack.IsEmpty())
    {
        printf("error in line %d\n", __LINE__);
    }

    if (1 != stack.Count())
    {
        printf("error in line %d\n", __LINE__);
    }

    if (1.5 != stack.Top())
    {
        printf("error in line %d\n", __LINE__);
    }

    stack.Push(2);
    if (stack.IsEmpty())
    {
        printf("error in line %d\n", __LINE__);
    }

    if (2 != stack.Count())
    {
        printf("error in line %d\n", __LINE__);
    }

    if (2 != stack.Top())
    {
        printf("error in line %d\n", __LINE__);
    }

    stack.Push(3);
    if (stack.IsEmpty())
    {
        printf("error in line %d\n", __LINE__);
    }

    if (3 != stack.Count())
    {
        printf("error in line %d\n", __LINE__);
    }

    if (3 != stack.Top())
    {
        printf("error in line %d\n", __LINE__);
    }

    stack.Pop();
    if (stack.IsEmpty())
    {
        printf("error in line %d\n", __LINE__);
    }

    if (2 != stack.Count())
    {
        printf("error in line %d\n", __LINE__);
    }

    if (2 != stack.Top())
    {
        printf("error in line %d\n", __LINE__);
    }
}

void TestStrInStack()
{
    Stack <Str> stack;

    if (!stack.IsEmpty())
    {
        printf("error in line %d\n", __LINE__);
    }

    if (0 != stack.Count())
    {
        printf("error in line %d\n", __LINE__);
    }

    stack.Push("Ori");
    if (stack.IsEmpty())
    {
        printf("error in line %d\n", __LINE__);
    }

    if (1 != stack.Count())
    {
        printf("error in line %d\n", __LINE__);
    }

    if ("Ori" != stack.Top())
    {
        printf("error in line %d\n", __LINE__);
    }

    stack.Push("Mirit");
    if (stack.IsEmpty())
    {
        printf("error in line %d\n", __LINE__);
    }

    if (2 != stack.Count())
    {
        printf("error in line %d\n", __LINE__);
    }

    if ("Mirit" != stack.Top())
    {
        printf("error in line %d\n", __LINE__);
    }

    stack.Push("Itay");
    if (stack.IsEmpty())
    {
        printf("error in line %d\n", __LINE__);
    }

    if (3 != stack.Count())
    {
        printf("error in line %d\n", __LINE__);
    }

    if ("Itay" != stack.Top())
    {
        printf("error in line %d\n", __LINE__);
    }

    stack.Pop();
    if (stack.IsEmpty())
    {
        printf("error in line %d\n", __LINE__);
    }

    if (2 != stack.Count())
    {
        printf("error in line %d\n", __LINE__);
    }

    if ("Mirit" != stack.Top())
    {
        printf("error in line %d\n", __LINE__);
    }
}

