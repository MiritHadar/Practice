/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_logMsg
#define __OL67_logMsg

#include <iostream>
#include "uncopyable.hpp"

using namespace std;

namespace ilrd
{

enum Severity
{
    SDEBUG = 0,
    INFO = 1,
    WARNING = 2,
    ERROR = 3
};

/**************************************LogMsg***************************************/
class LogMsg
{
public:
    //explicit LogMsg() = delete
    explicit LogMsg(string msg_ = "", ostream &stream_ = cout,
                                                        Severity severity_ = ERROR);
    LogMsg(const LogMsg &other_);
    //LogMsg& operator=(LogMsg &other_) = default
    //~LogMsg() = default
    string &GetStr();
    ostream &GetOstream();

private:
    string m_str;
    ostream *m_stream;
    Severity m_severity;
};

/**************************************Functor**************************************/
class FuncPrintLogMsg
{
public:
    void operator()(LogMsg &msg_);
};

} // namespace ilrd

#endif /* __OL67_logMsg */


