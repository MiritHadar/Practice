/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <string>
#include "circle.hpp"

using namespace std;

namespace ilrd
{

Circle::Circle(COLORS color_, Point center_, double angle_, double radius_)
    : Shape::Shape(color_, center_, angle_, radius_, CIRC)
{
    ;
}

void Circle::Draw()
{
    DrawCircle(m_color, m_center.GetX(), m_center.GetY(), m_len);
}


/* void Circle::DeSerialize(std::string& str_)
{
    stringstream stream;
    stream << str_;
    cout << "my stream: " << stream.str() << endl;
    string shapeType;
    stream >> shapeType;

    //center
    double x = 0;
    double y = 0;
    stream >> x;
    stream >> y;
    cout << x << " " << y << endl;
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
    cout << "angle:" << angle << endl;

    //radius
    double radius = 0;
    stream >> radius;
    SetLength(radius);

    cout << GetPosition() << " "  << GetColor() << " " << GetAngle() << " " << GetLength() << " " << endl;
} */


} //namespace ilrd
