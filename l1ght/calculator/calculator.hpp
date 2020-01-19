/******************************************************************************/
/* author: 		Mirit Hadar											  	      */
/* version: 	Final			  		                                      */
/* Last update: 							                                  */
/******************************************************************************/

#ifndef L1GHT_CALCULATOR
#define L1GHT_CALCULATOR

#if __cplusplus < 201103L
#define nullptr NULL
#define noexcept throw()
#endif

#include <vector>      	    //  vector
#include <fstream>			//  ifstream
#include <stdexcept>		// 	runtime_error
#include <dlfcn.h>			//	dlerror
#include <cerrno>			//	errno
#include <cstring>			//	strerror

#include "uncopyable.hpp"	// For inaccessible CCtor and assign operator
#include "stack.hpp"		// My Stack
#include "parser.hpp"

namespace l1ght
{

class Calculator : private Uncopyable
{

public:
	// Ctors (CCtors Blocked)
	
	// Funcs
	std::vector<double> Calculate(const char fileName_[]);
	void SortBetweenStacks();
	void Execute();
	
private:
	static Stack<int> m_numbersStack;
	//static Stack<char> m_operatorsStack;
};

class FileDoesntOpen : public std::runtime_error
{
public:
	explicit FileDoesntOpen(const std::string &errorString_ = "");
private:

};

} // namespace l1ght

#endif  //L1GHT_CALCULATOR
