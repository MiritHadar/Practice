/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_factory
#define __OL67_factory

#include <iostream>         // I / O
#include <map>              //  map
#include "shared_ptr.hpp"   // shared_ptr
#include "uncopyable.hpp"   // uncopyable

namespace ilrd
{

template <typename KEY_T, typename T>
class Factory : public Uncopyable
{
public:
    //Factory() = default
    //Factory(Factory& other_) = default
    //operator=(Factory& other_) = default
    SharedPtr <T> Create(const KEY_T& key_);
    void Learn (const KEY_T& key_, SharedPtr<T> (*func)());
    //~Factory() = defult

private:
    std::map <KEY_T, SharedPtr<T>(*)()> m_funcsPtrMap;
};

struct NullFuncPtr
{
    
};

template <typename KEY_T, typename T>
SharedPtr<T> Factory<KEY_T, T>::Create(const KEY_T& key_)
{
    SharedPtr<T> (*objectCreatorFunc)() = m_funcsPtrMap[key_];

	if (nullptr == objectCreatorFunc)
	{
		throw NullFuncPtr();
	}

	return objectCreatorFunc();
}

template <typename KEY_T, typename T>
void Factory<KEY_T, T>::Learn(const KEY_T& key_, SharedPtr<T> (*func_)())
{
    m_funcsPtrMap[key_] = func_;
}


} // namespace ilrd

#endif /* __OL67_factory */


