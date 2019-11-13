/******************************************************************************/
/* author: 		Mirit Hadar											  	  */
/* Reviewer: 					       										  */
/* version: 	Draft			  		                                      */
/* Last update: 20-10-2019					                                  */
/******************************************************************************/

#ifndef ILRD_RD6768_FD_LISTENER
#define ILRD_RD6768_FD_LISTENER

#if __cplusplus < 201103L
#define nullptr NULL
#define noexcept throw()
#endif

#include <vector>			//	vector, pair

#include "uncopyable.hpp"	// 	For inaccessible CCtor and assign operator

namespace ilrd
{

class FDListener : private Uncopyable
{
public:
    enum FDMode
    {
        READ = 0,
        WRITE = 1,
        EXCEPT = 2
    };

	typedef int FD;
	typedef std::pair<FD, FDMode> FDPair;
    typedef std::vector< FDPair > FDVector;

    //Constructors
    //explicit FDListener() = default;
    //~FDListener() noexcept = default;

	//Operators
	FDVector operator()(FDVector fDsToListen_, long timeoutSec_);
};

class FDListenerOperatorException : public std::runtime_error
{
public:
	explicit FDListenerOperatorException(const std::string &s_ = "");

private:
};

}//namespace ilrd

#endif  //ILRD_RD6768_FD_LISTENER
