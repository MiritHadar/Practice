/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "loggerMT.hpp"

namespace ilrd
{
LoggerMT::LoggerMT(ostream &stream_, Severity severity_)
    : m_stream(&stream_),
      m_writer(),
      m_severity(severity_)
{
    ;
}

void LoggerMT::Log(string msg_, Severity severity_)
{
    if (m_severity <= severity_)
    {
        LogMsg msgToSend(msg_, *m_stream, severity_);
        LogMsg copyMsg(msgToSend);
        m_writer.PushMsg(copyMsg);
    }
}

void LoggerMT::SetOutput(ostream &stream_)
{
    m_stream = &stream_;
}

void LoggerMT::SetSeverity(Severity severity_)
{
    m_severity = severity_;
}

} // namespace ilrd



