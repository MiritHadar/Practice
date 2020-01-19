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

#include <fstream>			// file stream
#include <stdexcept>		// 	runtime_error
#include <dlfcn.h>			//	dlerror
#include <cerrno>			//	errno
#include <cstring>			//	strerror

#include "uncopyable.hpp"	// For inaccessible CCtor and assign operator
#include "stack.hpp"		// My Stack

namespace l1ght
{

class Parser : private Uncopyable
{

public:
	// Ctors (CCtors Blocked)
	//explicit Parser();
	~Parser() noexcept = default;

	// Funcs
	static void Parse(const char fileName_[]);
	static std::string CopyFromFileToBuff(const char fileName_[]);

private:
	static Stack<int> m_numbersStack;
	static Stack<char> m_operatorsStack;
};

class FileDoesntOpen : public std::runtime_error
{
public:
	explicit FileDoesntOpen(const std::string &errorString_ = "");
private:

};

} // namespace l1ght

#endif  //L1GHT_PARSER
