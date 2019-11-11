/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "logMsg.hpp"

namespace ilrd
{

LogMsg::LogMsg(string msg_, ostream &stream_, Severity severity_)
    : m_str(msg_), m_stream(&stream_), m_severity(severity_)
{
    ;
}

LogMsg::LogMsg(const LogMsg &other_)
    : m_str(other_.m_str), m_stream(other_.m_stream)
{
    ;
}

string& LogMsg::GetStr()
{
    return m_str;
}

ostream& LogMsg::GetOstream()
{
    return *m_stream;
}

/**************************************Functor***************************************/

void FuncPrintLogMsg::operator()(LogMsg& msg_) 
{
	msg_.GetOstream() << msg_.GetStr();
}


} // namespace ilrd


