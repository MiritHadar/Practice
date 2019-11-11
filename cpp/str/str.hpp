/*
********************************************************************************

Developer : Mirit Hadar
Reviewer : Ben Eliezer
Last Update : 8/8/19
Status : Approved

********************************************************************************
*/


#ifndef __OL67_str
#define __OL67_str

#include <cstring>  // str funcs 
#include <cstdio>   //   I / o c
#include <cassert>  //  assert   
#include <ostream>	// ostream
#include <iostream>	// I / O cpp


class Str
{
public:
    /* Ctor Dtor*/
    /* will work for both const char* and const char[]=string literal */
    Str(const char* str_ = "");         //copy assign Ctor
    Str(const Str& o_str_);             //copy Ctor
    //Str& operator=(const Str& o_str_);  assign to str object
    ~Str();
    /* Operator */
    //Str& operator=(const char* other_); assign to char*
    Str& operator=(const Str& o_str_); //assign to Str

    char& operator[](size_t index);        //can read from and write to
    const char& operator[](size_t index) const;   //can read from const can't write to it

    Str& operator+=(const Str& o_str_);
    bool operator<(const Str& o_str_) const;
    bool operator>(const Str& o_str_) const;
    Str& operator+(const Str& o_str_);
    friend std::ostream& operator<<(std::ostream& os_, const Str& str_);

    /* Funcs */
    char *ToCString() const;
    void PrintStr() const;
    size_t GetLength() const;

    /* Data */
private:
    mutable char *m_str;
};

/* External Operators - accept Str's and char**/
bool operator==(const Str& str1_, const Str& str2_);
bool operator!=(const Str& str1_, const Str& str2_);

#endif /* __OL67_str */


