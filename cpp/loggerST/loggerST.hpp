/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_loggerST
#define __OL67_loggerST

#include "uncopyable.hpp"
#include "loggerMT.hpp"
#include "shared_ptr.hpp"

#if __cplusplus < 201103L
#define nullptr NULL
#define noexcept throw()
#endif

extern "C"
{
    ilrd::LoggerMT* GetSOInstance();
}

namespace ilrd
{

class LoggerST : private Uncopyable
{
    public:
        static LoggerMT *GetInstance();

    private:
        static LoggerMT *m_pInstance;
        explicit LoggerST();
};

} // namespace ilrd

#endif /* __OL67_loggerST */


