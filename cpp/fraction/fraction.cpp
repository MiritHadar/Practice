/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include "fraction.hpp"
#include <cassert>      /* assert */

namespace ilrd
{
    const Fraction g_undefined(1, 0);
    //initialize to -1 because of the gloabl Fraction defined above
    int Fraction::CounterObj = -1;

    Fraction::Fraction(int up_, int down_)
        :m_up(up_), m_down(down_)
    {
        m_up = up_;
        m_down = down_;
        ++CounterObj;
    }

    void Fraction::PrintCntr()
    {
        printf("CounterObj = %d\n", CounterObj);
    }
    /****************************************Operators*****************************************/
    int Fraction::operator==(const Fraction& other_f_) const
    {
        return ((m_up * other_f_.m_down) == (m_down * other_f_.m_up));
    }

    int Fraction::operator!=(const Fraction& other_f_) const
    {
        return !(*this == other_f_);
    }

    /* Unary minus 
    Fraction Fraction::operator-() const
    {
        Fraction tmp(m_up * 1, m_down);

        return tmp;
    }*/

    /* Unary plus 
    Fraction Fraction::operator+() const
    {
        return *this;
    }*/

    /* Prefix */
    Fraction& Fraction::operator--()
    {
        m_up -= m_down;

        return *this;
    }

    Fraction& Fraction::operator++()
    {
        m_up += m_down;

        return *this;
    }

    /* PostFix */
    Fraction Fraction::operator++(int dummy)
    {
        Fraction tmp = *this;
        m_up += m_down;

        return tmp;
    }

    Fraction Fraction::operator--(int dummy)
    {
        Fraction tmp = *this;
        m_up -= m_down;

        return tmp;
    }

    /* Binary Minus */
    Fraction Fraction::operator-(const Fraction& other_f_) const
    {
        Fraction tmp(m_up * other_f_.m_down - other_f_.m_up * m_down, m_down * other_f_.m_down);
    
        return tmp;
    }

    /* Binary Plus */
    Fraction Fraction::operator+(const Fraction& other_f_) const
    {
        Fraction tmp(m_up * other_f_.m_down + other_f_.m_up * m_down, m_down * other_f_.m_down);
        if (other_f_.GetIsUnDefined() || GetIsUnDefined())
        {
            return g_undefined;
        }
        return tmp;
    }

    /* Plus assignment */
    Fraction& Fraction::operator+=(const Fraction& other_f_)
    {
        m_up = m_up * other_f_.m_down + m_down * other_f_.m_up;
        m_down = m_down * other_f_.m_down;

        return *this;
    }

    /* minus assignment */
    Fraction& Fraction::operator-=(const Fraction& other_f_)
    {
        m_up = m_up * other_f_.m_down - m_down * other_f_.m_up;
        m_down = m_down * other_f_.m_down;

        return *this;
    }

    /****************************************Funcs***************************************/
    bool Fraction::GetIsUnDefined() const
    {
        return m_down == 0;
    }

    void Fraction::AddToSelf(const Fraction& f_)
    {
        if (0 == f_.m_down || 0 == m_down)
        {
            m_up = 1;
            m_down = 0;
        }
        else
        {
            m_up = m_up * f_.m_down + m_down * f_.m_up;
            m_down *= f_.m_down;
        }
    }

    void Fraction::AddToSelf(int num_)
    {
        if (0 != m_down)
        {
            m_up += (num_ * m_down);
        }
    }

    void Fraction::Print() const
    {
        printf("%d/%d\n", m_up, m_down);
    }

    bool Fraction::IsEqual(const Fraction& f_) const
    {
        if (0 == f_.m_down || 0 == m_down)
        {
            return 0;
        }

        return ((f_.m_up * m_down) == (m_up * f_.m_down));
    }

    bool Fraction::IsEqual(int num_) const
    {
        if (0 == m_down)
        {
            return 0;
        }

        return ((num_ * m_down) == (m_up * 1));
    }

    int Fraction::GetUp() const
    {
        return m_up;
    }

    int Fraction::GetDown() const
    {
        return m_down;
    }

    void Fraction::SetUp(int num_) const
    {
        m_up = num_;
    }

    void Fraction::SetDown(int num_)
    {
        m_down = num_;
    }

    std::ostream& operator<<(std::ostream& os_, const Fraction& fr_)
    {
        return os_ << fr_.m_up << "/" << fr_.m_down << std::endl;
    }

}//namespace ilrd
