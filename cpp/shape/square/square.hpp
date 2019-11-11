/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_SQUARE
#define __OL67_SQUARE

#include <string>   //string
#include "rect.hpp"

namespace ilrd
{
    class Square : public Rect
    {
    public:
        /*non-exp*/ Square(COLORS color_ = COLOR_WHITE, Point center_ = Point(0,0), double angle_ = 0, double len_ = 0);
};
  
} // namespace ilrd


#endif /* __OL67_SQUARE */


