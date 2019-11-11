/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_LINE
#define __OL67_LINE

#include <string>   //string
#include "shape.hpp"

namespace ilrd
{

class Line : public Shape
{
public:
    /*non-explicit*/ Line(COLORS color_ = COLOR_WHITE, Point center_ = Point(0,0), double angle_ = 0, double len_ = 0);
    void Draw();
    //std::string Serialize() const;
    //~Line() = delete;
};

} // namespace ilrd

#endif /* __OL67_LINE */


