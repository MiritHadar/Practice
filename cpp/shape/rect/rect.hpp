/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_RECT
#define __OL67_RECT

#include <string>

#include "shape.hpp"

namespace ilrd
{
    class Rect : public Shape
    {
    public:
        /*non-explicit*/ Rect(COLORS color_ = COLOR_WHITE, Point center_ = Point(0,0), double angle_ = 0, double width_ = 0, double height_ = 0);
        virtual void Draw();
        std::string Serialize() const;
        double GetHeight() const;
        void SetHeight(double height);
        
    private:
        double m_height;
    };
} // namespace irld

#endif /* __OL67_RECT */


