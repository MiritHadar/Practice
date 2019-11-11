/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_CIRCLE
#define __OL67_CIRCLE

#include "shape.hpp"


namespace ilrd
{

class Circle : public Shape
{
//friend std::ostream& operator<<(std::ostream& os_, Circle &circle_);

public:
    //Circle() = default;
    /*non-explicit*/ Circle(COLORS color_= COLOR_WHITE, Point center_ = Point(0,0), double angle_ = 0, double radius_ = 0);
    void Draw();
    //std::string Serialize() const;
    //void DeSerialize(std::string& str_);
    //~Circle() = delete;
private:

};

} //namespae ilrd


#endif /* __OL67_CIRCLE */


