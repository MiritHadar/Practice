/******************************************************************************/
/* Author: 		Mirit Hadar											  	      */
/* Version: 	Final			  		                                      */
/* Last update: 22-01-2020						                              */
/******************************************************************************/

#ifndef L1GHT_PARSER
#define L1GHT_PARSER

#if __cplusplus < 201103L
#define nullptr NULL
#define noexcept throw()
#endif

#include <vector>      	    // vector
#include <fstream>			// ifstream
#include <cerrno>			// errno

#include "uncopyable.hpp"	// For inaccessible CCtor and assign operator

namespace l1ght
{

class Parser : private Uncopyable
{
public:
	explicit Parser() = default;
	~Parser() noexcept = default;
	std::vector<std::string> Parse(const char fileName_[]);
};

class FileDoesntOpen : public std::runtime_error
{
public:
	explicit FileDoesntOpen(const std::string &errorString_ = "");
};

} // namespace l1ght

#endif  //L1GHT_PARSER
