/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "surpriser.hpp"

typedef Surpriser *(*ctors)(void);
typedef void (*SrandForFirstRun)(void);

static Surpriser *InitPrint();
static Surpriser *InitSystem();
static Surpriser *InitCreateFile();

static void DoNothing();
static void ExecSrand();

Surpriser *GetRandomSurprise(void)
{    
    static ctors ctorLookUpTable[NUM_OF_SURPRISES] = 
    {
        InitPrint,
        InitSystem,
        InitCreateFile
    };
    
    static SrandForFirstRun Srnad[2] =
    {
        ExecSrand,
        DoNothing
    };
int
    static int flag = 0;
    Srnad[flag]();
    flag = 1;

    int rand_num  = rand() % NUM_OF_SURPRISES;
    
    return ctorLookUpTable[rand_num]();
}

void Surpriser::SurpriseMe(void) const
{
    ;
}

void Print::SurpriseMe(void) const
{
    cout << "Surprise!!!!!!!!!" <<endl;
}

void System::SurpriseMe(void) const
{
    system("echo -e '\\a'");
}

void CreateFile::SurpriseMe(void) const
{
    ofstream myfile;
    myfile.open ("nothing_here.txt");
    myfile.close();
    cout << "File opened"<<endl;
}

static Surpriser *InitPrint()
{
    return new Print;
}

static Surpriser *InitSystem()
{
    return new System;
}

static Surpriser *InitCreateFile()
{
    return new CreateFile;
}

static void DoNothing()
{
    ;
}

static void ExecSrand()
{
    srand(time(NULL));
}

