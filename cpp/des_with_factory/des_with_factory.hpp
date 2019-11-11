/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_des_with_factory
#define __OL67_des_with_factory

#include <vector>       //vector
#include <string>       //string 
#include <sstream>      //stringstream 
#include "factory.hpp"

namespace ilrd
{
template <typename T>
class DesByFactory
{
public:
    std::vector<SharedPtr> Deserialize(std::stringstream& strSream_);
private:
    vector m_vec;
}

} // namespace ilrd
#endif /* __OL67_des_with_factory */


