/******************************************************************************/
/* Author: 		Mirit Hadar											  	      */
/* Version: 	Final			  		                                      */
/* Last update: 22-01-2020						                              */
/******************************************************************************/

#ifndef L1GHT_CALCULATOR
#define L1GHT_CALCULATOR

#if __cplusplus < 201103L
#define nullptr NULL
#define noexcept throw()
#endif

#include <vector>      	    // vector
#include <fstream>			// ifstream
#include <stdexcept>		// runtime_error
#include <cerrno>			// errno
#include <cstring>			// strerror
#include <sstream>          // stringstream
#include <stack>			// stack	

#include "uncopyable.hpp"	// For inaccessible CCtor and assign operator
#include "parser.hpp"		// add

namespace l1ght
{

class Calculator : private Uncopyable
{

public:
	// Ctor
	explicit Calculator();
	//default dtor

	std::vector<double> Calculate(const char fileName_[]);

private:
	// Funcs
	double Execute(std::string str_);
	//int ConvertStrIntoNum(std::string str_);

	// Data members
	static std::stack<double> m_numbersStack;
	static std::stack<char> m_operatorsStack;
};

} // namespace l1ght

#endif // L1GHT_CALCULATOR
