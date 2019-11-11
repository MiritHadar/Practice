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
    //BitSet(const BitSet<N>& other_) = default      
    //BitSet<N>& operator=(const BitSet<N>& other_) = default 
    //~BitSet() = default

//Operators
    BitSet<N>& operator&=(const BitSet<N>& other_);
    BitSet<N>& operator|=(const BitSet<N>& other_);
    BitSet<N>& operator^=(const BitSet<N>& other_);
    BitSet<N> operator~() const;

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

    MachineWord* GetStartArr() const;
    MachineWord* GetEndArr() const;

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
    MachineWord operator()(const MachineWord& firstNum_, const MachineWord& secondNum_)
    {
        return firstNum_ & secondNum_;
    }
};

struct OrOperator
{
    MachineWord operator()(const MachineWord& firstNum_, const MachineWord& secondNum_)
    {
        return firstNum_ | secondNum_;
    }
};

struct XorOperator
{
    MachineWord operator()(const MachineWord& firstNum_, const MachineWord& secondNum_)
    {
        return firstNum_ ^ secondNum_;
    }
};

struct TildeOperator
{
    MachineWord operator()(const MachineWord& num_)
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
BitSet<N> BitSet<N>::operator~() const
{
    BitSet<N> localBsForReturn;
    std::transform(this->GetStartArr(),
                   this->GetEndArr(),
                   localBsForReturn.GetStartArr(),
                   TildeOperator());

    return localBsForReturn;
}


template<size_t N>
bool BitSet<N>::operator[](size_t index_) const
{
	return (m_bitSetArr + (index_ / sizeof(*m_bitSetArr))) &
		   (1ULL << index_ % sizeof(*m_bitSetArr));
}

template<size_t N>
bool BitSet<N>::IsSet(size_t index_) const
{
    return /*static_cast<bool>( */(*this)[index_]/* ) */;
}


template<size_t N>
MachineWord* BitSet<N>::GetStartArr() const
{
	return const_cast<MachineWord*>(m_bitSetArr);
}

template<size_t N>
MachineWord* BitSet<N>::GetEndArr() const
{
	return const_cast<MachineWord*>(m_bitSetArr + m_numOfElemsInArr);
}

/************************************************************************/
template<size_t N>
BitSet<N> operator&(const BitSet<N>& first_, const BitSet<N>& second_)
{
    BitSet<N> localBsForReturn(first_);

    return localBsForReturn &= second_;
}


} // namespace ilrd
 
#endif /* __OL67_bitset */


