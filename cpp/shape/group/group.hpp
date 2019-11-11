/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_GROUP
#define __OL67_GROUP

#include <string>
#include <vector>       /*  vector  */
#include <algorithm>    /* for each */

#include "circle.hpp"
#include "line.hpp"
#include "square.hpp"
#include "shared_ptr.hpp"

namespace ilrd
{
using namespace std;
class Group : public Shape
{
public:
    //Group() = default;
    /*non-exp*/ Group(COLORS color_ = COLOR_BLACK, Point center_ = Point(0,0), double angle_ = 0);
    void SetPosition(const Point other_p_); /*override*/
    void SetAngle(double other_a_); /*override*/
    void Revolve(const Point& other_p_, double angle_); /*override*/
    void Draw(); /*override*/
    Group& Add(Shape *shape_);
    std::string Serialize() const;
    //void DeSerialize(std::string& str_);
    size_t GetNumOfShapes() const;
private:
    vector<Shape*>m_shapes;
    Point m_pos_change;
    double m_angle_change;
};


} // namespace ilrd


#endif /* __OL67_GROUP */


