/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "square.hpp"

using namespace std;

namespace ilrd
{

Square::Square(COLORS color_, Point center_, double angle_, double len_)
    : Rect::Rect(color_, center_, angle_, len_, len_)
{
    m_shape_name = SQUR;
}

} // namespace ilrd
