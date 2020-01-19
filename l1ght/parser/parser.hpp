/******************************************************************************/
/* author: 		Mirit Hadar											  	      */
/* version: 	Final			  		                                      */
/* Last update: 							                                  */
/******************************************************************************/

#ifndef L1GHT_PARSER
#define L1GHT_PARSER

#if __cplusplus < 201103L
#define nullptr NULL
#define noexcept throw()
#endif

#include <iostream>			//	ostream
#include <exception>		// exceptions
#include <fstream>			// file stream
#include <stdexcept>		// 	runtime_error
#include <dlfcn.h>			//	dlerror
#include <cerrno>			//	errno
#include <cstring>			//	strerror

#include "uncopyable.hpp"	// For inaccessible CCtor and assign operator

namespace l1ght
{

class Parser : private Uncopyable
{
public:
	explicit Parser() = delete;
	static void Parse(const char fileName_[]);
	~Parser() noexcept = default;

private:
	class ParserHelper
	{
		void OperFile();
		void TranselateToNums();
	};
};

class FileDoesntOpen : public std::runtime_error
{
public:
	explicit FileDoesntOpen(const std::string &errorString_ = "");
private:

};


} // namespace l1ght

#endif  //L1GHT_PARSER
