/******************************************************************************/
/* author: 		Mirit Hadar											  	  */
/* Reviewer: 					       										  */
/* version: 	Draft			  		                                      */
/* Last update: 24-09-2019					                                  */
/******************************************************************************/

#include "loggerMT.hpp"		//	Header file	

namespace ilrd
{

LoggerMT::LoggerMT(Severity severity_ , std::ostream *stream_)
    : m_severity(severity_), m_stream(stream_), m_writer()
{
	;
}

void LoggerMT::Log(Severity msgSeverity_, const char *msg_)
{
	if (m_severity <= msgSeverity_)
	{
		MsgFunctor msgF(LoggerMsg(msg_, m_stream));
		m_writer.WriteMsg(msgF);
	}
}

void LoggerMT::Log(Severity msgSeverity_, const std::string &msg_)
{
	Log(msgSeverity_, msg_.c_str());
}

void LoggerMT::SetOutputSeverity(Severity outputSeverity_)
{
	m_severity = outputSeverity_;
}

ilrd::LoggerMT::Severity LoggerMT::GetOutputSeverity() const
{
	return m_severity;
}

void LoggerMT::SetOutput(std::ostream &output_)
{
	m_stream = &output_;
}

/******************************************************************************/

LoggerMsg::LoggerMsg(const std::string msg_, std::ostream *stream_)
	: m_msg(msg_), m_stream(stream_)
{
	;
}

LoggerMsg::LoggerMsg(const LoggerMsg &other_)
	: m_msg(other_.m_msg), m_stream(other_.m_stream)
{
	;
}

std::string LoggerMsg::GetMsg() const
{
	return m_msg;
}

std::ostream *LoggerMsg::GetStream() const
{
	return m_stream;
}

/******************************************************************************/

MsgFunctor::MsgFunctor()
	: m_loggerMsg()
{
	;
}
MsgFunctor::MsgFunctor(LoggerMsg loggerMsg_)
	: m_loggerMsg(loggerMsg_)
{
	;
}

void MsgFunctor::operator()() 
{
	*m_loggerMsg.GetStream() << m_loggerMsg.GetMsg();
	(*m_loggerMsg.GetStream()).flush();
	
}

}//namespace ilrd
