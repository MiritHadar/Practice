/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_test_str
#define __OL67_test_str

#include <iostream>
#include <ostream>
#include <cstddef>
#include <cstring>

class String
{
public:
    String(const char* str_ = "");
    String(const String& other_);
    ~String();
    friend std::ostream& operator<<(std::ostream& os_, const String& str_);

private:
    char* m_str;
};


#endif /* __OL67_test_str */


