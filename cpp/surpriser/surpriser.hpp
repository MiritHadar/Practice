/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_surpriser
#define __OL67_surpriser

#include <cstdlib>      /* time, rand */  
#include <iostream>     /*    cout    */
#include <fstream>      /*  ofstream  */

#define     NUM_OF_SURPRISES         3
#define     TIMES_OF_RUN            10

using namespace std;

class Surpriser
{
public:
    virtual void SurpriseMe(void) const;
};

class Print : public Surpriser
{
    void SurpriseMe(void) const;
};

class System : public Surpriser
{
    void SurpriseMe(void) const;
};

class CreateFile : public Surpriser
{
    void SurpriseMe(void) const;
};

Surpriser *GetRandomSurprise(void);

#endif /* __OL67_surpriser */


