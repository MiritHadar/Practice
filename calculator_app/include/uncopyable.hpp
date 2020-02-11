/******************************************************************************/
/* Author: 		    Mirit Hadar											  	  */
/* Version: 	    Final			  		                                  */
/* Last update:     22-01-2020						                          */
/******************************************************************************/

#ifndef UNCOPYABLE
#define UNCOPYABLE

namespace mirit
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

} // namespace mirit

#endif // UNCOPYABLE