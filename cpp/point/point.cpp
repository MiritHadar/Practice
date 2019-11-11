/*
********************************************************************************

Developer : Mirit Hadar
Revier :
Last Update : 
Status :

********************************************************************************
*/

#include "point.hpp"
#include <math.h>
#include <stddef.h>

size_t g_total = 0;

Point::Point()
    : m_x(10), m_y(20), m_len(-1), m_p_len(&m_len)
{
    puts("initializing");
}

Point &Point::AdjustBy(const Point& p2_)
{
    m_x += p2_.m_x;
    m_y += p2_.m_y;
    m_len = -1;
    Length();
    
    return *this;
}

void Point::Length(void) const
{
    if (-1 == m_len)
    {
       *m_p_len = sqrt(((int(m_x)^2) + ((int(m_y)^2))));
       /*printf("%.2f\n", sqrt(((int(m_x)^2) + ((int(m_y)^2)))));*/ 
       g_total += m_len;
       printf("length : %f\n", m_len);
    }
}

void Point::Print(char open_, char close_) const
{
    printf("%c%.2f,%.2f%c\n", open_, m_x, m_y, close_);
}

void Point::Print(Parenth par_type_) const
{
    static const char *par_options = "<>[]{}()";
    size_t par_inx = par_type_ * 2;
    Print(*(par_options + par_inx), *(par_options + par_inx + 1));
}

Point Add(Point p1_, Point p2_)
{
    p1_.m_x += p2_.m_x;
    p1_.m_y += p2_.m_y;
    p1_.m_len = -1;
    p1_.Length();

    return p1_;
}

void Point::CheckLimit()
{
/*     cout << x << endl << y <<endl << limit << endl;
 */    if(m_x >= m_limit || m_y >= m_limit)
    {
        puts("you passet the limit");
    }
}

void Point::AdjustBy(int dx_, int dy_)
{
    m_x += dx_;
    m_y += dy_;
}

bool Point::IsEqual(Point p2_)
{
    if((p2_.m_x == m_x) && (p2_.m_y == m_y))
    {
        return true;
    }

    return false;
}

size_t SumOfLengths(Point p1)
{
    static size_t sum = 0;
    sum += p1.m_len;

    return sum;
}

void Sum()
{
    printf("%lu\n", g_total);
}
