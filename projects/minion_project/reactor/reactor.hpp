/******************************************************************************/
/* author: 		Mirit Hadar											  	      */
/* Reviewer: 					       										  */
/* version: 	Final			  		                                      */
/* Last update: 23-10-2019					                                  */
/******************************************************************************/

#ifndef ILRD_RD6768_REACTOR
#define ILRD_RD6768_REACTOR

#if __cplusplus < 201103L
#define nullptr NULL
#define noexcept throw()
#endif

#include <map>					// 	map
#include <boost/function.hpp>	// 	boost::function
#include <boost/bind.hpp>		// 	boost::bind for functions

#include "uncopyable.hpp"		// 	For inaccessible CCtor and assign operator
#include "fd_listener.hpp"		//	select function


namespace ilrd
{

class Reactor : public Uncopyable
{
public:

	static const FDListener::FD MAX_FD = 1024;
	typedef std::map<std::pair<FDListener::FD, FDListener::FDMode>, 							 boost::function<void(void)>/**/> FDMap;
	typedef boost::function<void(void)> ReactorFunction;
    //Constructors
    explicit Reactor();
    //~Reactor() noexcept = default;

    //Functions

	//Allows for function override
	//function can't throw exceptions  
    void AddFD(FDListener::FD fd_, 
			   FDListener::FDMode mode_, 							ReactorFunction action_);

	void RemoveFD(FDListener::FD fd_, FDListener::FDMode mode_);
	void Run();
	void Stop();

private:
    //Member variables
	FDMap m_fdToFunction;
	bool m_isRunning; 
};

class InvalidFDException : public std::runtime_error
{
public:
	explicit InvalidFDException(const std::string &errorString_ = "");

private:
};

class KeyNotExistException : public std::runtime_error
{
public:
	explicit KeyNotExistException(const std::string &s_ = "");

private:
};

}//namespace ilrd

#endif  //ILRD_RD6768_REACTOR
