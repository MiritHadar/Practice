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
#include <sstream>          // stringstream
#include <stack>			// stack	

#include "uncopyable.hpp"	// For inaccessible CCtor and assign operator
#include "parser.hpp"

namespace l1ght
{

class Calculator : private Uncopyable
{

public:
	// Ctor
	explicit Calculator();
	
	// Funcs
	std::vector<double> Calculate(const char fileName_[]);

private:
	// Funcs
	double Execute(std::string str_);
	//int ConvertStrIntoNum(std::string str_);

	// Data members
	static std::stack<int> m_numbersStack;
	static std::stack<char> m_operatorsStack;
};

} // namespace l1ght

#endif  //L1GHT_CALCULATOR
