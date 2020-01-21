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


#include "uncopyable.hpp"	// For inaccessible CCtor and assign operator
#include "stack.hpp"		// My Stack
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
	//static void SortBetweenStacks(std::string arithmetic_);
	double Execute(std::string str_);
	int ConvertToNum(std::string::const_iterator it);


	// Data members
	Stack<int> m_numbersStack;
	Stack<char> m_operatorsStack;
};

} // namespace l1ght

#endif  //L1GHT_CALCULATOR
