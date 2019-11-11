/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef __OL67_bitset
#define __OL67_bitset

#include <iostream>
#include <cstddef>

#include <algorithm>        //for_each

#if __cplusplus < 201103L
    #define nullptr (NULL)
#endif


namespace ilrd
{
/* 
template<typename T>
class Iterator
{
    Iterator<T>& operator++();
    T& opartor*();
    bool operator==(const Iterator<T>& itr2_);
};
*/

typedef size_t MachineWord;
typedef unsigned long long largestType;

const size_t NUM_TO_ASCII = 48;

template<size_t N>
class BitSet
{
private:
    class BitProxy;   //Forward Declaration

public:
//Ctors
    explicit BitSet();
    //explicit BitSet(largestType initialValue_);
    //BitSet(const BitSet<N>& other_) = default;       
    //BitSet<N>& operator=(const BitSet<N>& other_) = default;  
    //~BitSet() = default

//Operators
    BitSet<N>& operator&=(const BitSet<N>& other_);
    BitSet<N>& operator|=(const BitSet<N>& other_);
    BitSet<N>& operator^=(const BitSet<N>& other_);
    BitSet<N> operator~();

    bool operator[](size_t index_) const;
    BitProxy operator[](size_t index_);
    //ToDo: add operator<<

//Function
    BitSet<N>& SetBit(size_t index_, bool onOrOff_);
    bool IsSet(size_t index_) const;
    BitSet<N>& FlipBit(size_t index_);
    std::string ToString();
    size_t CountSetBits();
    void CountBitsOnInByte(char byte);
    void CounterForSingleBit(char byte);

    BitSet<N>& SetAll();
    BitSet<N>& ClearAll();
    void PrintBitSet();
    char GetIndex(size_t index_);

private:
    static const int m_numOfElemsInArr = (N + __CHAR_BIT__ - 1) / __CHAR_BIT__;
    MachineWord m_bitSetArr[m_numOfElemsInArr];
    size_t bitsOn;

};

template<size_t N>
class BitSet<N>::BitProxy
{
public:
    BitProxy operator=(BitProxy& bitProxy_);
    //conversion operator
    //BitProxy& operator=(const char& c_);
    //~CharProxy = default
private:
    explicit BitProxy(BitSet<N>& bitSet_, size_t index_);
    MachineWord& m_bitSet;
    size_t m_index;
};

/***************************** Functors *******************************/
struct AndOperator
{
    largestType operator()(const largestType firstNum_, const largestType secondNum_)
    {
        return firstNum_ & secondNum_;
    }
};

struct OrOperator
{
    largestType operator()(const largestType firstNum_, const largestType secondNum_)
    {
        return firstNum_ | secondNum_;
    }
};

struct XorOperator
{
    largestType operator()(const largestType firstNum_, const largestType secondNum_)
    {
        return firstNum_ ^ secondNum_;
    }
};

struct TildeOperator
{
    largestType operator()(const largestType num_)
    {
        return ~num_;
    }
};
/***************************** External Operators *******************************/
template<size_t N>
bool operator==(const BitSet<N>& first_, const BitSet<N>& second_);

template<size_t N>
bool operator!=(const BitSet<N>& first_, const BitSet<N>& second_);

//operators
template<size_t N>
BitSet<N> operator&(const BitSet<N>& first_, const BitSet<N>& second_);

template<size_t N>
BitSet<N> operator|(const BitSet<N>& first_, const BitSet<N>& second_);

template<size_t N>
BitSet<N> operator^(const BitSet<N>& first_, const BitSet<N>& second_);

/*****************************Implementatin**************************************/
 template<size_t N>
BitSet<N>::BitSet()
    :bitsOn(0)
{
    std::fill(m_bitSetArr, m_bitSetArr + m_numOfElemsInArr, '0');
}

/* template<size_t N>
BitSet<N>::BitSet(largestType initialValue_)
    :bitsOn(0)
{
    //todo init
    for (size_t i = m_numOfElemsInArr; i >= 0 ; --i)
    {
        unsigned long long digitFromInitValue = initialValue_ % 10;
        for (size_t j = __CHAR_BIT__; j >= 0 ; --j)
        {
            m_bitSetArr[i][j] = digitFromInitValue % 2;
        }
    }
} */

/* template<size_t N>
BitSet<N>::BitSet(const BitSet<N>& other_)
{
    std::copy(other_.m_bitSetArr, other_.m_bitSetArr + m_numOfElemsInArr, m_bitSetArr);
} */

template<size_t N>
BitSet<N>& BitSet<N>::FlipBit(size_t index_)
{
    SetBit(index_, !IsSet(index_));

    return *this;
}

template<size_t N>
std::string BitSet<N>::ToString()
{
    std::string str((N + 1), '0');
    str += N;
    &(str[N + 1]) = NULL;

    for (size_t i = m_numOfElemsInArr; i > 0; --i)
    {
        for (size_t j = __CHAR_BIT__; j > 0; --j)
        {
            str[j] = ((m_bitSetArr[i] >> j) & 1UL) + NUM_TO_ASCII;
        }
    }

    return str;
}
/* 
template<size_t N>
BitSet<N>& BitSet<N>::operator=(const BitSet<N>& other_)
{
    this->m_bitSetArr = other_->m_bitSetArr;

    return *this;
} */

template<size_t N>
BitSet<N>& BitSet<N>::operator&=(const BitSet<N>& other_)
{
    std::transform(other_.m_bitSetArr,
                    other_.m_bitSetArr + m_numOfElemsInArr,
                    m_bitSetArr,
                    m_bitSetArr,
                    AndOperator());

    return *this;
}


template<size_t N>
BitSet<N>& BitSet<N>::operator|=(const BitSet<N>& other_)
{
    std::transform(other_.m_bitSetArr,
                   other_.m_bitSetArr + m_numOfElemsInArr,
                   m_bitSetArr,
                   m_bitSetArr,
                   OrOperator());

    return *this;
}

template<size_t N>
BitSet<N>& BitSet<N>::operator^=(const BitSet<N>& other_)
{
    std::transform(other_.m_bitSetArr,
                   other_.m_bitSetArr + m_numOfElemsInArr,
                   m_bitSetArr,
                   m_bitSetArr,
                   XorOperator());

    return *this;
}

template<size_t N>
bool BitSet<N>::operator[](size_t index_) const
{
    size_t indexToSet = index_ / __CHAR_BIT__;
    unsigned long long mask = 1UL << (index_ % __CHAR_BIT__);

    return m_bitSetArr[indexToSet] & mask;
}

template<size_t N>
void BitSet<N>::PrintBitSet()
{
    for (int i = 0; i < m_numOfElemsInArr; i++)
    {
        std::cout << i << ": " << m_bitSetArr[i] << std::endl;
    }
}

template<size_t N>
BitSet<N>& BitSet<N>::SetBit(size_t index_, bool onOrOff_)
{
    size_t indexToSet = index_ / __CHAR_BIT__;
    unsigned long long mask = 1UL << (index_ % __CHAR_BIT__);

    m_bitSetArr[indexToSet] &= ~mask;       //turn bit off
    m_bitSetArr[indexToSet] |= (onOrOff_ << index_);

    return *this;
}

template<size_t N>
bool BitSet<N>::IsSet(size_t index_) const
{
    return (*this)[index_];
}

template<size_t N>
char BitSet<N>::GetIndex(size_t index_)
{
    return m_bitSetArr[index_];
}

template<size_t N>
size_t BitSet<N>::CountSetBits()
{
    //std::for_each(m_bitSetArr, m_bitSetArr + m_numOfElemsInArr, CountBitsOnInByte);

    return bitsOn;
}

template<size_t N>
void BitSet<N>::CountBitsOnInByte(char byte)
{
    std::for_each(m_bitSetArr, m_bitSetArr + __CHAR_BIT__ - 1, CounterForSingleBit(this));
}

template<size_t N>
void BitSet<N>::CounterForSingleBit(char byte)
{
    bitsOn += byte & 1UL;
}
/* 
template<size_t N>
bool operator==(const BitSet<N>& first_, const BitSet<N>& second_)
{

}

template<size_t N>
bool operator!=(const BitSet<N>& first_, const BitSet<N>& second_)
{

} */

//operators
template<size_t N>
BitSet<N> operator&(const BitSet<N>& first_, const BitSet<N>& second_)
{
    BitSet<N> localBsForReturn(first_);

    return localBsForReturn &= second_;
}

template<size_t N>
BitSet<N> operator|(const BitSet<N>& first_, const BitSet<N>& second_)
{
    BitSet<N> localBsForReturn(first_);

    return localBsForReturn |= second_;
}

template<size_t N>
BitSet<N> operator^(const BitSet<N>& first_, const BitSet<N>& second_)
{
    BitSet<N> localBsForReturn(first_);

    return localBsForReturn ^= second_;
}

template<size_t N>
BitSet<N> operator~(const BitSet<N>& bitSet_)
{
    BitSet<N> localBsForReturn(bitSet_);
    std::transform(bitSet_.m_bitSetArr,
                   bitSet_.m_bitSetArr + localBsForReturn.m_numOfElemsInArr,
                   localBsForReturn.m_numOfElemsInArr,
                   TildeOperator());

    return localBsForReturn;
}


/**************************************Iterator implementation****************************************/



} // namespace ilrd
 
#endif /* __OL67_bitset */


