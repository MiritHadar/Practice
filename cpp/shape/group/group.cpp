/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <string>
#include "group.hpp"

using namespace std;

namespace ilrd
{

Group::Group(COLORS color_, Point center_, double angle_)
    : Shape::Shape(color_, center_, angle_, 0, GRUP), m_pos_change(0, 0), m_angle_change(0)
{
    ;
}

void Group::Revolve(const Point& other_p_, double angle_)
{
    Point originCenter(m_center);
    m_center.Revolve(other_p_, Radyan(angle_));
    m_pos_change += originCenter - m_center;
}

void Group::SetPosition(const Point other_p_)
{
    m_pos_change += other_p_ - m_center;

    Shape::SetPosition(other_p_);
}

void Group::SetAngle(double other_a_)
{
    m_angle_change += other_a_ - m_angle;

    Shape::SetAngle(other_a_);
}
    
Group& Group::Add(Shape *shape_)
{
    /* SetPosition((shape_->GetPosition()) - m_pos_change);
    SetAngle(shape_->GetAngle() + m_angle_change); */

    m_shapes.push_back(shape_);

    return *this;
}

void Group::Draw()
{
    for(size_t i = 0; i < m_shapes.size(); ++i)
    {
        m_shapes[i]->SetPosition(m_shapes[i]->GetPosition() + m_pos_change);
        m_shapes[i]->Revolve(this->GetPosition(), m_angle_change);
        m_shapes[i]->SetAngle(m_shapes[i]->GetAngle() + m_angle_change); 
        m_shapes[i]->SetColor(m_color);
        m_shapes[i]->Draw();
    }

    m_pos_change = Point(0,0);
    m_angle_change = 0;
}

size_t Group::GetNumOfShapes() const
{
    return m_shapes.size();
}


string Group::Serialize() const
{
    stringstream stream;
    string str;
    stream << g_lut[m_shape_name] << this->GetPosition().GetX()  << " " <<
              this->GetPosition().GetY()  << " " <<         
              this->GetColor()            << " " << 
              this->GetAngle();

    for(size_t i = 0; i < m_shapes.size(); ++i)
    {
        stream << m_shapes[i]->Serialize();
    }

    str += stream.str();

    return str;
}

/* void Group::DeSerialize(std::string& str_)
{
    stringstream stream;
    stream << str_;
    string shapeType;
    stream >> shapeType;
    cout << "shapeType : " << shapeType << endl;

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

    string shapeInfo;

    m_angle_change = 0;
    m_pos_change = Point(0, 0);
    
    for(size_t i = 0; i < m_shapes.size(); ++i)
    {
        getline(stream, shapeInfo);
            cout << "shapeInfo : " << shapeInfo << endl;

        m_shapes[i]->DeSerialize(shapeInfo);
    }
} */

} //namespace ilrd