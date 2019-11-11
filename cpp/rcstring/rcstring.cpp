/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "rcstring.hpp"

namespace ilrd
{

static const size_t COUNTER_SIZE = 8;

static char *CreateRcstrFromStr(const char *str);

/* Ctor cstring */
RcString::RcString(const char* str_)
    : m_CntrAndStr(CreateRcstrFromStr(str_))
{
    ;
}

/* Ctor class string */
RcString::RcString(const RcString& other_)
    : m_CntrAndStr(other_.m_CntrAndStr)
{
    this->Increment();
}

/* returns the string in a struct */
const char* RcString::ToCString() const
{
    return m_CntrAndStr + COUNTER_SIZE;
}

/* Assignment operator to obj class - supports self assignment*/
RcString& RcString::operator=(const RcString& other_)
{
    other_.Increment();
    DecrementAndDeleteIfNeeded();

    m_CntrAndStr = other_.m_CntrAndStr;
    
    return *this;
}

RcString& RcString::operator+=(const RcString& other_)
{
    size_t len_me = strlen(m_CntrAndStr + COUNTER_SIZE);
    size_t len_o = strlen(other_.m_CntrAndStr + COUNTER_SIZE);

    char *concatenated = new char [len_me + len_o + 1 + COUNTER_SIZE];  // alloc space for counter + string

    memcpy(concatenated + COUNTER_SIZE, m_CntrAndStr + COUNTER_SIZE, len_me);
    memcpy(concatenated + len_me + COUNTER_SIZE, other_.m_CntrAndStr + COUNTER_SIZE, len_o + 1);

    DecrementAndDeleteIfNeeded();

    m_CntrAndStr = concatenated;
    concatenated = nullptr;

    *(reinterpret_cast<size_t*>(m_CntrAndStr)) = 1;

    return *this;
}

char RcString::operator[](size_t index_) const
{
    return (m_CntrAndStr + COUNTER_SIZE)[index_];
}

RcString::CharProxy RcString::operator[](size_t index_)
{
    RcString::CharProxy charInIndex(*this, index_);

    return charInIndex;
}


std::ostream& operator<<(std::ostream& os_, const RcString& rcStr_)
{
    return os_ << rcStr_.ToCString();
}


void RcString::PrintStr() const
{
    std::cout << m_CntrAndStr + COUNTER_SIZE << std::endl;
}

size_t RcString::GetLength() const
{
    return strlen(m_CntrAndStr + COUNTER_SIZE);
}

bool RcString::operator<(const RcString& other_) const
{
    return (strcmp(m_CntrAndStr + COUNTER_SIZE, other_.m_CntrAndStr + COUNTER_SIZE) < 0);
}

bool RcString::operator>(const RcString& other_) const
{
    return (strcmp(m_CntrAndStr + COUNTER_SIZE, other_.m_CntrAndStr + COUNTER_SIZE) > 0);
}

RcString::~RcString()
{
    DecrementAndDeleteIfNeeded();
}

size_t RcString::GetCounter() const
{
    return *(reinterpret_cast<size_t*>(m_CntrAndStr)); 
}

void RcString::DeleteIfNeeded()
{
    if (0 == *m_CntrAndStr)
    {
        delete[] m_CntrAndStr;     m_CntrAndStr = nullptr;
    }
}

void RcString::Increment() const
{
    ++*(reinterpret_cast<size_t*>(m_CntrAndStr));
}

void RcString::Decrement()
{
    --*(reinterpret_cast<size_t*>(m_CntrAndStr));
}

void RcString::DecrementAndDeleteIfNeeded()
{
    this->Decrement();
    this-> DeleteIfNeeded();
}

/*****************************CharProxy************************************/
RcString::CharProxy::CharProxy(RcString &rcStr_,size_t i_)
    : m_rcStr(rcStr_), m_index(i_)
{
    ;
}

RcString::CharProxy RcString::CharProxy::operator=(CharProxy& charProxy_)
{
    return *this = charProxy_.m_rcStr.ToCString()[m_index];
}

RcString::CharProxy& RcString::CharProxy::operator=(const char& c_)
{
    if (1 != *(m_rcStr.m_CntrAndStr))
    {
        m_rcStr.Decrement();
        m_rcStr.m_CntrAndStr = CreateRcstrFromStr(m_rcStr.m_CntrAndStr);
		*(reinterpret_cast<size_t*>(m_rcStr.m_CntrAndStr)) = 1;
	}

	(m_rcStr.m_CntrAndStr + COUNTER_SIZE)[m_index] = c_;

    return *this;
}

RcString::CharProxy::operator char() const
{
    return (m_rcStr.m_CntrAndStr + COUNTER_SIZE)[m_index];
}

/***************************** External Operators *******************************/
/* Returns 1 when both objects are equal. accepts casting */
bool operator==(const RcString& str1_, const RcString& str2_)
{
    return !strcmp(str1_.ToCString(), str2_.ToCString());
}

/* Returns 1 when objects are non-equal. accepts casting */
bool operator!=(const RcString& str1_, const RcString& str2_)
{
    return !(str1_ == str2_);
}

/*******************************Static*******************************************/
static char *CreateRcstrFromStr(const char *str)
{
    assert(str);

    size_t size = strlen(str) + 1;
	char *dest = new char[size + COUNTER_SIZE];

    memcpy(dest + COUNTER_SIZE, str, size);
    *(reinterpret_cast<size_t*>(dest)) = 1;

	return dest;
}

} // namespace ilrd









