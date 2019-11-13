/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_loggerMT
#define __OL67_loggerMT

#include "logMsg.hpp"
#include "thread.hpp"
#include "waitable_queue.hpp"
#include "uncopyable.hpp"
#include "writer.hpp"

#include <iostream>

namespace ilrd
{

class LoggerMT : public Uncopyable
{
public:
    explicit LoggerMT(ostream &stream_ = cout, Severity severity_ = ERROR);
    void Log(string msg_ = "", Severity severity_ = ERROR);
    void SetOutput(ostream &stream_);
    void SetSeverity(Severity severity_);

private:
    ostream *m_stream;
    Writer m_writer;
    Severity m_severity;
};

} // namespace ilrd

#endif /* __OL67_loggerMT */


