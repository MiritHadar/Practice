/******************************************************************************/
/* author: 		Mirit Hadar											  	  */
/* Reviewer: 					       										  */
/* version: 	Draft			  		                                      */
/* Last update: 24-09-2019					                                  */
/******************************************************************************/

#ifndef ILRD_RD6768_LOGGERMT
#define ILRD_RD6768_LOGGERMT

#if __cplusplus < 201103L
#define nullptr NULL
#define noexcept throw()
#endif

#include <iostream>			//	string, ostream

#include "uncopyable.hpp"
#include "writer.hpp"

namespace ilrd
{

class MsgFunctor;

class LoggerMT : private Uncopyable
{
public:
    enum Severity
    {
        SDEBUG = 0,
        INFO = 1,
        WARNING = 2,
        ERROR = 3
    };

    //Constructors
    explicit LoggerMT(Severity severity_ = WARNING, 
					  std::ostream *stream_ = &std::cerr);
    //~LoggerMT()noexcept = default;

    //Operators

    //Functions
    void Log(Severity msgSeverity_, const char *msg_);
    void Log(Severity msgSeverity_, const std::string &msg_);

    void SetOutputSeverity(Severity outputSeverity_);
	Severity GetOutputSeverity() const;
    void SetOutput(std::ostream &output_);   

private:
    //Member variables
    Severity m_severity;
    std::ostream *m_stream;
	Writer<MsgFunctor> m_writer;
};

/******************************************************************************/

class LoggerMsg 
{
public:
    //Constructors
    explicit LoggerMsg(const std::string msg_ = "", 
						std::ostream *stream_ = &std::cerr);
    LoggerMsg(const LoggerMsg &other_);
    //~LoggerMsg()noexcept = default;

    //Operators
    //LoggerMsg& operator=(const LoggerMsg& other_) = default;

    //Functions
    std::string GetMsg() const;
	std::ostream *GetStream() const;

private:
    //Member variables
	std::string m_msg;
	std::ostream *m_stream;
};

/******************************************************************************/

class MsgFunctor 
{
public:
    //Constructors
	explicit MsgFunctor();
    explicit MsgFunctor(LoggerMsg loggerMsg_);
    //MsgFunctor(const MsgFunctor& other_) = default;
    //~MsgFunctor()noexcept = default;

    //Operators
    //MsgFunctor& operator=(const MsgFunctor& other_) = default;
	void operator()();
    //Functions

private:
    //Member variables
	LoggerMsg m_loggerMsg;
};

}//namespace ilrd

#endif  //ILRD_RD6768_LOGGERMT
