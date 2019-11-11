/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_SHAPE
#define __OL67_SHAPE

#include <ostream>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>      //stringstream
#include <vector>       //vector

#include <cmath>        // M_PI, sin, cos
#include "point.hpp"
#include "glut_utils.h"
#include "shared_ptr.hpp"

using namespace std;

namespace ilrd
{
inline double Radyan(double angle_);

const size_t g_NUM_OF_SHAPES = 5;
enum ShapeName{LINE, CIRC, RECT, SQUR, GRUP};
const string g_lut[g_NUM_OF_SHAPES] = {"line", "circ", "rect", "squr", "grup"};

class Shape
{

public:
    /*non-explicit*/ Shape(COLORS color_, Point center_, double angle_, double len_, ShapeName shape_name_);
    inline const Point &GetPosition() const;
    inline void SetPosition(const Point other_p_);

    inline double GetAngle() const;
    inline void SetAngle(double other_a_);

    inline COLORS GetColor() const;
    inline void SetColor(COLORS other_c_);
    
    inline double GetLength() const;
    inline void SetLength(double len_);

    virtual void Revolve(const Point& other_p_, double angle_);
    virtual void Draw() = 0;

    virtual std::string Serialize() const;

    virtual ~Shape() = 0;

protected:
    COLORS m_color;
    Point m_center;
    double m_angle;
    double m_len;
    ShapeName m_shape_name;
};


const Point& Shape::GetPosition() const
{
    return m_center;
}

void Shape::SetPosition(const Point other_p_)
{
    m_center = other_p_;
}

double Shape::GetAngle() const
{
    return m_angle;
}

void Shape::SetAngle(double other_a_)
{
    m_angle = Radyan(other_a_);
}

double Shape::GetLength() const
{
    return m_len;
}

void Shape::SetLength(double len_)
{
    m_len  = len_;
}


COLORS Shape::GetColor() const
{
    return m_color;
}

void Shape::SetColor(COLORS other_c_)
{
    m_color = other_c_;
}


/*********************************************************************************/
double Radyan(double angle_)
{
    return angle_ * M_PI / 180.0;
}



int KeyboardFunction(unsigned char key, int x, int y);

} //namespae ilrd

#endif /* __OL67_SHAPE */


