/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_MUTEX
#define __OL67_MUTEX

namespace ilrd
{

class Mutex
{
public:
    explicit Mutex()
        : m_IsLocked(1)
    {
        ;
    }

    void lock()
    {
        m_IsLocked = 1;
    }

    void unlock()
    {
        m_IsLocked = 0;
    }

    bool IsLocked()
    {
        return m_IsLocked;
    }

    ~Mutex()
    {
        m_IsLocked = 0;
    }

private:
    bool m_IsLocked;
};

}//namespace ilrd

#endif /* __OL67_MUTEX */


