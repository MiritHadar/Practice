/*
********************************************************************************

Developer : Mirit Hadar
Reviewer :
Last Update : 
Status :

********************************************************************************
*/

#ifndef ILRD_RD6768_SHAREDPTR
#define ILRD_RD6768_SHAREDPTR

#include <cstddef>          /*  size_t  */

#if __cplusplus < 201103L
    #define nullptr NULL
#endif

namespace ilrd
{

template <typename T>
class SharedPtr
{
public:
    //Constructors
    SharedPtr(T* ptr_ = nullptr);
    SharedPtr(const SharedPtr& other_);
    ~SharedPtr();

    //friend
    template <typename OT> friend class SharedPtr<T>;

    //Operators
    template <typename OT>
    operator SharedPtr<OT>();  // convert

    // Regular assign
    SharedPtr& operator=(const SharedPtr& other_);

    // Template assign
    template <typename OT>         
    SharedPtr<T>& operator=(const SharedPtr<OT>& other_);

    T& operator*();
    T* operator->();
    
    //Functions
    T *GetRawPtr();

private:
    //Member variables
    T *m_ptr;
    size_t *m_counter;

};

template <typename T>
SharedPtr<T>::SharedPtr(T* ptr_)
    : m_ptr(ptr_), m_counter(new size_t(1))
{
    ;
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& other_)
    : m_ptr(other_.m_ptr), m_counter(other_.m_counter)
{
    ++(*m_counter);
}

template <typename T>
SharedPtr<T>::~SharedPtr()
{
    --(*m_counter);

    if (0 == *m_counter)
    {
        delete m_ptr;   m_ptr = nullptr;
        delete m_counter;
    }
}

/* Convert */
template <typename T>
template <typename OT>
SharedPtr<T>::operator SharedPtr<OT>()  
{
    SharedPtr<OT> new_type;
    delete new_type.m_counter;

    new_type.m_ptr = m_ptr;
    new_type.m_counter = m_counter;

    ++(*m_counter);

    return new_type;
}

/* Regular assingment - self assign safe */
template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& other_)
{
    ++*other_.m_counter;
    --*m_counter;

    if (0 == *m_counter)
    {
        delete m_counter;
        delete m_ptr;
    }

    m_counter = other_.m_counter;
    m_ptr = other_.m_ptr;

    return *this;
}

/* Template - self assign safe */
template <typename T>
template <typename OT>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<OT>& other_)
{
    ++*other_.m_counter;
    --*m_counter;

    if (0 == *m_counter)
    {
        delete m_counter;
        delete m_ptr;
    }

    m_counter = other_.m_counter;
    m_ptr = other_.m_ptr;

    return *this;
}

template <typename T>
T& SharedPtr<T>::operator*() 
{
    return *m_ptr;
}

template <typename T>
T* SharedPtr<T>::operator->() 
{
    return m_ptr;
}

template <typename T>
T *SharedPtr<T>::GetRawPtr()
{
    return m_ptr;
}

}//namespace ilrd

#endif  /*ILRD_RD6768_SHAREDPTR*/
