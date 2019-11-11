/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "shape.hpp"

using namespace std;

namespace ilrd
{

Shape::Shape(COLORS color_, Point center_, double angle_, double len_, ShapeName shape_name_)
    : m_color(color_), m_center(center_), m_angle(Radyan(angle_)), m_len(len_), m_shape_name(shape_name_)
{
    ;
}

Shape::~Shape()
{
    ;
}

void Shape::Revolve(const Point& other_p_, double angle_)
{
    m_center.Revolve(other_p_, Radyan(angle_));
}

string Shape::Serialize() const
{
    stringstream stream;
    string str;
    stream <<  g_lut[m_shape_name] << " " << this->GetColor() << " " <<
               this->GetPosition().GetX()  << " " <<
               this->GetPosition().GetY()  << " " <<         
               this->GetAngle()            << " " <<
               this->GetLength();

    str +=  stream.str();
    cout << "str: " << str << endl;
    return str;
}

int KeyboardFunction(unsigned char key, int x, int y)
{
    cout << "Keyboard: " << key << x << y <<endl;

    if (key == 0x1b /* ESC */)
        return -1;

    return 0;
}



} //namespae ilrd

