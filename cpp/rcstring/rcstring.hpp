/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_RCSTRING
#define __OL67_RCSTRING

#include <cstring>  // str funcs 
#include <cassert>  // assert
#include <ostream>	// ostream
#include <iostream>	// I / O

#define     nullptr     NULL

namespace ilrd
{

class RcString
{   
    friend std::ostream& operator<<(std::ostream& os_, const RcString& rcStr_);
private:
    class CharProxy; //Forward Declaration

public:
    //Ctors
    /*non-explicit*/ RcString(const char* str_ = "");         //copy assign Ctor
    RcString(const RcString& other_);    //copy Ctor
    //Str& operator=(const Str& other_);  assign to str object
    ~RcString();
    // Operator
    RcString& operator=(const RcString& other_); //assign to Str

    char operator[](size_t index_) const;   //can read from const can't write to it
    CharProxy operator[](size_t index_);
    RcString& operator+=(const RcString& other_);
    bool operator<(const RcString& other_) const;
    bool operator>(const RcString& other_) const;

    // Funcs
    const char *ToCString() const;
    void PrintStr() const;
    size_t GetLength() const;
    size_t GetCounter() const;

private:
    void Increment() const;
    void Decrement();
    void DeleteIfNeeded();
    void DecrementAndDeleteIfNeeded();
    char *m_CntrAndStr;

    class CharProxy
    {
    public:
        explicit CharProxy(RcString& rcStr_, size_t i_);
        operator char() const;  //conversion operator
        CharProxy& operator=(const char& c_);
        //~CharProxy = default
    private:
        CharProxy operator=(CharProxy& charProxy_);
        RcString &m_rcStr;
        size_t m_index;
    };
};

/* External Operators - accept Str's and char**/
bool operator==(const RcString& str1_, const RcString& str2_);
bool operator!=(const RcString& str1_, const RcString& str2_);
} // namespace ilrd

#endif /* __OL67_RCSTRING */


