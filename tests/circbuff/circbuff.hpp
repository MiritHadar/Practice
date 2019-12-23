/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#include <cstddef>

#ifndef __OL67_circbuff
#define __OL67_circbuff

template <typename T>
class CircBuffer
{
public:
    /* non explicit */ CircBuffer(size_t capacity_ = 10);
    ~CircBuffer();
    T Peek() const;
    size_t GetSize() const;
    size_t GetCapacity() const;
    void Add(T newItem);
    void Remove();

private:
    CircBuffer() {}
    T *m_arr;
    size_t m_size;
    const size_t m_capacity;
    size_t m_frontIndx;      //first free index
};

template <typename T>
CircBuffer<T>::CircBuffer(size_t capacity_)
    : m_arr(new T[capacity_]),
      m_capacity(capacity_),
      m_size(0),
      m_frontIndx(0)	
{
    ;
}

template <typename T>
CircBuffer<T>::~CircBuffer()
{
    delete m_arr;
}

template <typename T>
T CircBuffer<T>::Peek() const
{
    if (m_size > 0)
    {
        return m_arr[m_frontIndx];
    }

    return NULL;
}

template <typename T>
size_t CircBuffer<T>::GetSize() const
{
    return m_size;
}

template <typename T>
size_t CircBuffer<T>::GetCapacity() const
{
    return m_capacity;
}

template <typename T>
void CircBuffer<T>::Add(T newItem)
{
    if (m_capacity > m_size)
    {
        m_arr[m_frontIndx] = newItem;
        m_frontIndx = (m_frontIndx + 1) % m_capacity;
        ++m_size;
    }
}

template <typename T>
void CircBuffer<T>::Remove()
{
    if (m_size > 0)
    {
        if (m_frontIndx == 0)
        {
            m_frontIndx = m_capacity;
        }

        m_frontIndx = m_frontIndx - 1;
        --m_size;
    }
}

#endif /* __OL67_circbuff */


