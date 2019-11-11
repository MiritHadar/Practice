/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_deserialize
#define __OL67_deserialize

#include <vector>
#include <string>
#include "shape.hpp"
#include "shared_ptr.hpp"

namespace ilrd
{
    std::vector<SharedPtr<Shape> > Deserialize(std::string& str_);
}

#endif /* __OL67_deserialize */


