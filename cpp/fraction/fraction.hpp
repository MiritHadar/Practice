/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_fraction
#define __OL67_fraction

#include <cstdio>   /* printf */
#include <ostream>
#include <iostream>

namespace ilrd
{
    class Fraction
    {
        static int CounterObj;
        //size_t obj_num;

    public:

        explicit Fraction(int up_ = 0, int down_ = 1);
        int operator==(const Fraction& other_f_) const;
        int operator!=(const Fraction& other_f_) const;

/*         operator int() { return m_up / m_down; }
 */        operator float() { return m_up / m_down; }

        /* Unaries */
        inline Fraction operator-() const;
        inline Fraction operator+() const;
        
        /* PreFix */
        Fraction& operator--();
        Fraction& operator++();
        
        /* PostFix */
        Fraction operator++(int dummy);
        Fraction operator--(int dummy);
        
        /* Binary */
        Fraction operator-(const Fraction& other_f_) const;
        Fraction operator+(const Fraction& other_f_) const;
        
        /* Assign */
        Fraction& operator-=(const Fraction& other_f_);
        Fraction& operator+=(const Fraction& other_f_);

        bool GetIsUnDefined() const;
        void AddToSelf(const Fraction& f_);
        void AddToSelf(int num_);
        void Print() const;
        bool IsEqual(const Fraction& f_) const;
        bool IsEqual(int num_) const;
        friend std::ostream& operator<<(std::ostream& os_, const Fraction& fr_);

        int GetUp() const;
        int GetDown() const;
        void SetUp(int num_) const;
        void SetDown(int num_);

        static void PrintCntr();

        mutable int m_up;
        mutable int m_down;
    };

    //Fraction operator+(const Fraction& f1_, const Fraction& f2_);
    const Fraction ZERO(0,1);
    const Fraction HALF(1,2);
    const Fraction ONE(1,1);

    /* Unary minus */
    inline Fraction Fraction::operator-() const
    {
        Fraction tmp(m_up * 1, m_down);

        return tmp;
    }

    /* Unary plus */
    inline Fraction Fraction::operator+() const
    {
        return *this;
    }

}//namespace ilrd

#endif /* __OL67_fraction */


