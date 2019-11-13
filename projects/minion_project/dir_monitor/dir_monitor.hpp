/******************************************************************************/
/* author: 		Mirit Hadar											  	  */
/* Reviewer: 					       										  */
/* version: 	Draft			  		                                      */
/* Last update: 29-10-2019					                                  */
/******************************************************************************/

#ifndef ILRD_RD6768_DIR_MONITOR
#define ILRD_RD6768_DIR_MONITOR

#if __cplusplus < 201103L
#define nullptr NULL
#define noexcept throw()
#endif

#include <string>				// 	string
#include <boost/function.hpp>	// 	boost::function

#include "uncopyable.hpp"		// 	For inaccessible CCtor and assign operator
#include "service_locator.hpp"	//	ServiceLocator header
#include "dl_loader.hpp"		//	DLLoader header

namespace ilrd
{

class DirMonitor : private Uncopyable
{
public:

	typedef int FD;
	typedef boost::function<void(std::string)> CallBack;
    //Constructors
    explicit DirMonitor(const std::string &path_, CallBack callBack_, 										ServiceLocator<std::string> &serviceLocator_);
    //~DirMonitor() noexcept = default;

    //Operators

    //Functions
	FD GetFD() const;
	void ReactorFunc();

private:
    //Member variables
	std::string m_path;
	FD m_inotifyFD;
	CallBack m_callBack;
	ServiceLocator<std::string> &m_serviceLocator;
	DlLoader m_dlLoader;
};

}//namespace ilrd

#endif  //ILRD_RD6768_DIR_MONITOR
