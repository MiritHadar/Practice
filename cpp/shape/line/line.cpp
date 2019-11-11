/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "line.hpp"

using namespace std;

namespace ilrd
{
Line::Line(COLORS color_, Point center_, double angle_, double len_)
    : Shape::Shape(color_, center_, angle_, len_, LINE)
{
    ;
}

void Line::Draw()
{
    double x = m_center.GetX();
    double y = m_center.GetY();
    double new_len = m_len / 2.0;

    Point begin(x + (new_len * cos(m_angle)), y + (new_len * sin(m_angle)));
    Point end(x + (new_len * cos(m_angle + M_PI)), y + (new_len * sin(m_angle + M_PI)));

    /* begin.Revolve(m_center, rd_angle);
    end.Revolve(m_center, rd_angle); */

    DrawPolygon(m_color, 2, int(begin.GetX()), int(begin.GetY()), int(end.GetX()), int(end.GetY()));
}

} //namespace ilrd

