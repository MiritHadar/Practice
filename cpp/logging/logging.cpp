/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "logging.hpp"

using namespace std;

namespace ilrd
{
Logger::Logger(Severity initialSeverity_)
    : m_severity(initialSeverity_)
{
    m_ostreams[false] = new ofstream("dev/null");
    m_ostreams[true] = &cerr;
}

void Logger::Log(Severity msgSeverity_, const char *msg_)
{
    *(m_ostreams[msgSeverity_ >= m_severity]) << msg_ << endl;
}

void Logger::Log(Severity msgSeverity_, const string &msg_)
{
    *(m_ostreams[msgSeverity_ >= m_severity]) << msg_ << endl;
}

void Logger::SetOutputSeverity(Severity outputSeverity_)
{
    m_severity = outputSeverity_;
}

void Logger::SetOutput(ostream &output_)
{
    m_ostreams[1] = &output_;
}

Logger::Severity Logger::GetSeverity()
{
    return m_severity;
}


} // namespace ilrd