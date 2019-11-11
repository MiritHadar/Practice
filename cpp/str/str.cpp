/*
********************************************************************************

Developer : Mirit Hadar
Reviewer : Ben Eliezer
Last Update : 8/8/19
Status : Approved

********************************************************************************
*/

#include "str.hpp"

static char *NewStrDup(const char *str);

/* Ctor cstring */
Str::Str(const char* str_)
    : m_str(NewStrDup(str_))
{
}

/* Ctor class string */
Str::Str(const Str& o_str_)
    : m_str(NewStrDup(o_str_.m_str))
{
}

/* returns the string in a struct */
char* Str::ToCString() const
{
    assert(m_str);
    return m_str;
}

/* Assignment operator to obj class - supports self assignment*/
Str& Str::operator=(const Str& o_str_)
{
    assert(&o_str_);
    char *tmp = NewStrDup(o_str_.m_str);
    delete[] m_str;

    m_str = tmp;

    return *this;
}

/* Assignment operator to char* 
Str& Str::operator=(const char* other_)
{
    *this = Str(other_);
    
    return *this;
}*/


Str& Str::operator+=(const Str& o_str_)
{
    assert(&o_str_);

    size_t len_me = strlen(m_str);
    size_t len_o = strlen(o_str_.m_str);

    char *tmp = new char [len_me + len_o + 1];

    strcpy(tmp, m_str);
    strcat(tmp + len_me, o_str_.m_str);

    delete[] m_str;
    m_str = NewStrDup(tmp);
    delete[] tmp;

    return *this;
}

char& Str::operator[](size_t index)
{
    return m_str[index];
}

const char& Str::operator[](size_t index) const
{
    return m_str[index];
}

std::ostream& operator<<(std::ostream& os_, const Str& str_)
{
    return os_ << str_.ToCString();
}


void Str::PrintStr() const
{
    printf("%s\n", m_str);
}

size_t Str::GetLength() const
{
    return strlen(m_str);
}

bool Str::operator<(const Str& o_str_) const
{
    return (strcmp(m_str, o_str_.m_str) < 0);
}

bool Str::operator>(const Str& o_str_) const
{
    return (strcmp(m_str, o_str_.m_str) > 0);
}

Str::~Str()
{
/*     printf("Dtor: %p\n", this);
 */    delete[] m_str;
}

/***************************** External Operators *******************************/
/* Returns 1 when both objects are equal. accepts casting */
bool operator==(const Str& str1_, const Str& str2_)
{
    return !strcmp(str1_.ToCString(), str2_.ToCString());
}

/* Returns 1 when objects are non-equal. accepts casting */
bool operator!=(const Str& str1_, const Str& str2_)
{
    return !(str1_ == str2_);
}

/*******************************Static*******************************************/
static char *NewStrDup(const char *str)
{
    size_t len = 1;

    if (NULL == str)
    {
        char *dest = new char[len];
        memcpy(dest, "", len);
        
        return dest;
    }

    len = strlen(str) + 1;
	char *dest = new char[len];
    memcpy(dest, str, len);

	return dest;
}





