/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_SCOPE_GUARD
#define __OL67_SCOPE_GUARD

namespace ilrd
{
    
template <typename T>
class ScopeGuard
{
    typedef void (T::*startfunc)();
    typedef void (T::*endfunc)();

public:
    explicit ScopeGuard(T& type_, startfunc startFunc_, endfunc endFunc_);
    //ScopeGuard(const ScopeGuard &other_) = default;
    //ScopeGuard operator=(const ScopeGuard &other_) = default;

    ~ScopeGuard() noexcept;

private:
    T& m_type;
    startfunc m_startFunc;
    endfunc m_end;
};

template <typename T>
ScopeGuard<T>::ScopeGuard(T& type_, startfunc startFunc_, endfunc endFunc_)
    : m_type(type_), m_startFunc(startFunc_), m_end(endFunc_)
{
    (m_type.*m_startFunc)();
}

template <typename T>
ScopeGuard<T>::~ScopeGuard() noexcept
{
    (m_type.*m_end)();
}

#endif /* __OL67_SCOPE_GUARD */

} // namespace ilrd