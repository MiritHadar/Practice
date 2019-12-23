

#ifndef _uncopyable
#define _uncopyable

#include <pthread.h>        /*  Threads  */

namespace mobileye
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

}//namespace mobileye

#endif// _uncopyable