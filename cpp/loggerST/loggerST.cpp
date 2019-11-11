/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "loggerST.hpp"

namespace ilrd
{

LoggerMT* LoggerST::m_pInstance = nullptr;

LoggerST::LoggerST()
{
   ;
}

LoggerMT* LoggerST::GetInstance()
{
    pthread_mutex_t mut;
    pthread_mutex_lock(&mut);

    if (nullptr == m_pInstance)
    {
        m_pInstance = new LoggerMT();
    }

    pthread_mutex_unlock(&mut);

    return m_pInstance;
}

} // namespace ilrd


extern "C"
{
    ilrd::LoggerMT* GetSOInstance()
    {
        return ilrd::LoggerST::GetInstance();
    }
}



