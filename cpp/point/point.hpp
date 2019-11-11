/*
********************************************************************************

Developer : Mirit Hadar
Revier :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_ws1_2
#define __OL67_ws1_2

#include <stdio.h>
#include <assert.h>
using namespace std;
#include <iostream>

extern size_t g_total;

struct Point
{    
    explicit Point();
    
    enum Parenth 
    {
        ANGULAR = 0,
        SQUARE = 1,
        CURLY = 2,
        ROUND = 3
    };

    double m_x;
    double m_y;
    double m_limit;
    double m_len;
    double *m_p_len;

    void AdjustBy(int dx_, int dy_);
    Point &AdjustBy(const Point& p2_);

    void Print(char open = '[', char close = ']') const;
    void Print(Parenth par_type_ = ROUND) const;

    void CheckLimit();
    bool IsEqual(Point p2_);
    void Length() const;
};

struct Counter
{
    int m_a;
    int m_b;
};


size_t SumOfLengths(Point p1);
void Sum();


#endif /* __OL67_ws1_2 */


