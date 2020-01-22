/******************************************************************************/
/* Author: 		Mirit Hadar											  	      */
/* Version: 	Final			  		                                      */
/* Last update: 22-01-2020						                              */
/******************************************************************************/

#ifndef L1GHT_UNCOPYABLE
#define L1GHT_UNCOPYABLE

#if __cplusplus < 201103L
#define nullptr NULL
#define noexcept throw()
#endif

namespace l1ght
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

} // namespace l1ght

#endif // L1GHT_UNCOPYABLE