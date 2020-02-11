/******************************************************************************/
/* Author: 		    Mirit Hadar											  	  */
/* Version: 	    Final			  		                                  */
/* Last update:     22-01-2020						                          */
/******************************************************************************/

#ifndef PARSER
#define PARSER

#include <vector>      	    // vector
#include <fstream>			// ifstream
#include <cerrno>			// errno

#include "uncopyable.hpp"	// For inaccessible CCtor and assign operator

namespace mirit
{

class Parser : private Uncopyable
{
public:
	// Ctors
	explicit Parser() = default;
	~Parser() noexcept = default;

	// Funcs
	std::vector<std::string> Parse(const char fileName_[]);
};

class FileDoesntOpen : public std::runtime_error
{
public:
	explicit FileDoesntOpen(const std::string &errorString_ = "");
};

} // namespace mirit

#endif  // PARSER
