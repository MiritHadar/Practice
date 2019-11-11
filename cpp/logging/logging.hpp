/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_logging
#define __OL67_logging

#include <string>
#include <iostream>
#include <fstream>      /* oftream */

#define     NUM_OF_STREAMS      2

using namespace std;

namespace ilrd
{

class Logger
{
public:
    enum Severity
    {
        SDEBUG = 0,
        INFO = 1,
        WARNING = 2,
        ERROR = 3
    };

    //explicit Logger(const char *str_);
    explicit Logger(Severity initialSeverity_ = WARNING);

    void Log(Severity msgSeverity_, const char *msg_);
    void Log(Severity msgSeverity_, const string &msg_);

    void SetOutputSeverity(Severity outputSeverity_);
    void SetOutput(ostream &output_);

    Severity GetSeverity();

private:
    Severity m_severity;
    ostream *m_ostreams[NUM_OF_STREAMS];
};

} // namespace ilrd

#endif /* __OL67_logging */


