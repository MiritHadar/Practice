/******************************************************************************/
/* Author: 		    Mirit Hadar											  	  */
/* Version: 	    Final			  		                                  */
/* Last update:     22-01-2020						                          */
/******************************************************************************/

#ifndef L1GHT_CALCULATOR
#define L1GHT_CALCULATOR

#include <vector>      	    // vector
#include <stack>			// stack	

#include "parser.hpp"		// parser class header

namespace l1ght
{

class Calculator : private Uncopyable
{
	friend class Handler;
	friend class Executer;

public:
	// Ctors
	explicit Calculator();
	~Calculator() = default;

	// Funcs
	std::vector<double> Calculate(const char fileName_[]);

private:
	// Data members
	std::stack<double> m_numbersStack;
	std::stack<char> m_operatorsStack;

	// Funcs
	double Execute(std::string str_);
};

} // namespace l1ght

#endif // L1GHT_CALCULATOR
