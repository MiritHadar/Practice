

#ifndef ILRD_RD6768_UNCOPYABLE
#define ILRD_RD6768_UNCOPYABLE

#include <pthread.h>        /*  Threads  */

namespace ilrd
{

class Uncopyable
{
protected:
    explicit Uncopyable()
    {
        ;
    }
    virtual ~Uncopyable()
    {
        ;
    }

private:
    Uncopyable(const Uncopyable &other_);
    Uncopyable &operator=(const Uncopyable &other_);
};

}//namespace ilrd

#endif//ILRD_RD6768_UNCOPYABLE