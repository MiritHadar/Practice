/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <stdlib.h>      //itoa
#include "rect.hpp"

using namespace std;

namespace ilrd
{
Rect::Rect(COLORS color_, Point center_, double angle_, double width_, double height_)
    : Shape::Shape(color_, center_, angle_, width_, RECT), m_height(height_)
{
    ;
}

void Rect::Draw()
{
    double half_width = m_len / 2;
    double half_height = m_height / 2;

    Point p1(m_center.GetX() - half_width, m_center.GetY() - half_height);
    Point p2(m_center.GetX() + half_width, m_center.GetY() - half_height);
    Point p3(m_center.GetX() + half_width, m_center.GetY() + half_height);
    Point p4(m_center.GetX() - half_width, m_center.GetY() + half_height);

    p1.Revolve(m_center, m_angle);
    p2.Revolve(m_center, m_angle);
    p3.Revolve(m_center, m_angle);
    p4.Revolve(m_center, m_angle);

    DrawPolygon(m_color, 4, static_cast<int>(p1.GetX()), static_cast<int>(p1.GetY()),
                            static_cast<int>(p2.GetX()), static_cast<int>(p2.GetY()),
                            static_cast<int>(p3.GetX()), static_cast<int>(p3.GetY()),
                            static_cast<int>(p4.GetX()), static_cast<int>(p4.GetY()));
}

double Rect::GetHeight() const
{
    return m_height;
}

void Rect::SetHeight(double height)
{
    m_height = height;
}

string Rect::Serialize() const
{
    stringstream stream;
    string str;
    stream << g_lut[m_shape_name] << this->GetPosition().GetX()  << " " <<
              this->GetPosition().GetY()  << " " <<         
              this->GetColor()            << " " << 
              this->GetAngle()            << " " <<
              this->GetLength()           << " " <<
              this->GetHeight();

    str +=  stream.str();

    return str;
}

/* void Rect::DeSerialize(std::string& str_)
{
    stringstream stream;
    stream << str_;
    string shapeType;
    stream >> shapeType;

    //center
    double x = 0;
    double y = 0;
    stream >> x;
    stream >> y;
    Point p(x, y);
    SetPosition(p);

    //color
    int color = 0;
    stream >> color;
    SetColor(COLORS(color));

    //angle
    double angle = 0;
    stream >> angle;
    SetAngle(angle);

    //radius
    double radius = 0;
    stream >> radius;
    SetLength(radius);

    double height = 0;
    stream >> height;
    SetHeight(height);
} */

} // namespace irld
