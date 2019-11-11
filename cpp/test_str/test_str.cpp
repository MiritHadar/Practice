/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "test_str.hpp"

static char *NewStrdup(const char *str_);

String::String(const char* str_)
    : m_str(NewStrdup(str_))
{
    ;
}

String::String(const String& other_)
    : m_str(NewStrdup(other_.m_str))
{
    ;
}

String::~String()
{
    delete[] m_str;
}

std::ostream& operator<<(std::ostream& os_, const String& str_)
{
    return os_ << str_.m_str;
}

/******************************************************************/
static char *NewStrdup(const char *str_)
{
    size_t len = strlen(str_) + 1;
    char *dest = new char[len];
    memcpy(dest, str_, len);

    return dest;
}


