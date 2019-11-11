/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <stdio.h>
#include <bits/stdc++.h>      /*  exit             */

#include "exception_ex1.hpp"  /*	Header file    */

using namespace std;
using namespace ilrd;

int main()
{
    try
    {
        Bar();
    }
    catch (bad_alloc)
    {
        std::cerr << "out of memory! exiting.";
        exit(2);
    }
    catch (BadDog &b)
    {
        std::cerr << "Bad dog exception: " << b.what() << endl;
        exit(3);
    } 
    catch (exception &r)
    {
        std::cerr << "unknown exception: " << r.what() << endl;
        exit(4);
    }
    /* catch (...)
    {
        std::cerr << "default: "<< endl;
        exit(5);
    } */

    return 0;
}
